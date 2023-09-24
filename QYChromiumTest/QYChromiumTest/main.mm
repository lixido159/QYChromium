//
//  main.m
//  QYChromiumTest
//
//  Created by yinquan on 2023/8/16.
//

#import <Cocoa/Cocoa.h>
#import <QYView/QYEntry.h>
//int main(int argc, const char * argv[]) {
//    @autoreleasepool {
//        // Setup code that might create autoreleased objects goes here.
//    }
//    NSBundle *viewBundle = [NSBundle bundleWithIdentifier:@"qy.QYView"];
//    //TODO:临时解决，复制snapshot到Framework主目录
//    //V8_USE_EXTERNAL_STARTUP_DATA不知道为啥没有编译进去
//    initJS(viewBundle.resourcePath.UTF8String);
//    return NSApplicationMain(argc, argv);
//}

enum TOKEN_TYPE {
    tok_other = -1,//其他
    tok_eof = 0,//结束
    tok_identifier = 1,//标识符
    tok_number = 2,//数字
    tok_string = 3,//字符串 ""  ''
};

enum OPERATOR {
    opt_none = 0,
    opt_add = '+',//加
    opt_sub = '-',//减
    opt_mul = '*',//乘
    opt_div = '/',//除
};

#include <string>


class QYExpression {
public:
    virtual double getNumberValue(){ return 0; }
};

class QYNumberExpression : public QYExpression {
public:
    QYNumberExpression(double number):mNumber(number){};
    double mNumber;
    
    virtual double getNumberValue() override{
        return mNumber;
    }
};

class QYStringExpression : public QYExpression {
public:
    QYStringExpression(std::string str): mStr(str) {}
    std::string mStr;
};

class QYIdentifierExpression : public QYExpression{
public:
    QYIdentifierExpression(std::string var): mVar(var) {}
    std::string mVar;

};


class QYFunctionExpression : public QYExpression{
public:
    QYFunctionExpression(QYExpression *val, std::vector<QYExpression *> args): mVal(val), mArgs(args){};
    QYExpression *mVal;
    std::vector<QYExpression *> mArgs;
};

class QYPropertyAccessExpression : public QYExpression{
public:
    QYPropertyAccessExpression(QYExpression *callee, std::string property) : mCallee(callee), mProperty(property){};
    QYExpression *mCallee;
    std::string mProperty;
};

class QYCollectionAccessExpression : public QYExpression{
public:
    QYCollectionAccessExpression(QYExpression *callee, QYExpression *index): mCallee(callee), mIndex(index){};
    QYExpression *mCallee;
    //数组、字典都有可能
    QYExpression *mIndex;
};

class QYQuestionExpression : public QYExpression {
public:
    QYQuestionExpression(QYExpression *questionExp, QYExpression *trueExp, QYExpression *falseExp) : mQuestionExp(questionExp), mTrueExp(trueExp), mFalseExp(falseExp) {};
    QYExpression *mQuestionExp;
    QYExpression *mTrueExp;
    QYExpression *mFalseExp;
};

class QYBinaryExpression : public QYExpression {
public:
    QYBinaryExpression(QYExpression *leftExp, QYExpression *rightExp, OPERATOR opt):
    mLeftExp(leftExp), mRightExp(rightExp), mOpt(opt){};
    QYExpression *mLeftExp;
    QYExpression *mRightExp;
    OPERATOR mOpt;
    
    virtual double getNumberValue(){
        switch(mOpt) {
            case opt_add:
                return mLeftExp->getNumberValue() + mRightExp->getNumberValue();
            case opt_sub:
                return mLeftExp->getNumberValue() - mRightExp->getNumberValue();
            case opt_mul:
                return mLeftExp->getNumberValue() * mRightExp->getNumberValue();
            case opt_div:
                return mLeftExp->getNumberValue() / mRightExp->getNumberValue();
            default:
                throw "错误符号进行计算";
        }

        return mLeftExp->getNumberValue();
    }
};



struct QYToken {
    TOKEN_TYPE type;
    std::string identifier;
    double number;
    int chr;
};


//
class QYTokenParser {
public:
    std::string src;
    int curIndex = -1;
    //只能在getNextToken时使用
    int currentChar = ' ';
    //lastToken代表当前解析出来的token：字符串、数字、标识符、其他字符
    //currentChar代表token的下一个字符，最新位置的char
    QYToken lastToken;
    
    QYTokenParser(std::string str):src(str) {
        getNextToken();
    }
    
    int getNextChar() {
        currentChar = src[++curIndex];
        return currentChar;
    }
    
    int getCurrentInt() {
        return currentChar - '0';
    }
    
    int getCurrentChar() {
        return lastToken.chr;
    }
    
    
    
    void passSpace() {
        while(isspace(currentChar)) {
            getNextChar();
        }
    }
    
    QYToken getNextIdentifier() {
        std::string identifier;
        identifier += currentChar;
        while(isalnum(getNextChar())) {
            identifier += currentChar;
        }
        return {tok_identifier, identifier, 0};
    }
    
    QYToken getNextNumber() {
        std::string numberStr = std::to_string(getCurrentInt());
        while(isnumber(getNextChar()) || currentChar == '.') {
            numberStr += std::to_string(getCurrentInt());
        }
        return {tok_number, "", strtod(numberStr.c_str(), nullptr)};
    }
    
    QYToken getNextString() {
        //单引号还是双引号
        int quote = currentChar;
        std::string str;
        //遇到转义字符
        bool hasEscapeChar = false;
        while(true) {
            //到下一个字符
            getNextChar();
            //上一个是转义字符，这个不管是什么都加上
            if (hasEscapeChar) {
                hasEscapeChar = false;
                str.push_back(currentChar);
            }
            //遇到转义字符
            else if (currentChar == '\\') {
                hasEscapeChar = true;
            }
            //结束
            else if (currentChar == quote) {
                getNextChar();
                break;
            } else {
                str.push_back(currentChar);
            }
        }
        return {tok_string, "", 0};

    }
    
    QYToken getNextToken() {
        passSpace();
        //字母开头
        if (isalpha(currentChar)) {
            lastToken = getNextIdentifier();
        }
        //数字开头
        else if (isdigit(currentChar)) {
            lastToken = getNextNumber();
        }
        else if (currentChar == '\'' || currentChar == '"') {
            lastToken = getNextString();
        } else if (currentChar == '\0'){
            lastToken = {tok_eof, "", 0, currentChar};
        }
        //各种符号 + - * / ()等
        else {
            lastToken = {tok_other, "", 0, currentChar};
            getNextChar();
        }
        passSpace();
//        printf("打印 %s %lf %c\n", lastToken.identifier.c_str(), lastToken.number, lastToken.chr);
        return lastToken;
    };
    
    //括号、标识符、数字、字符串
    //这里代表一个新的解析的开始
    QYExpression* parsePrimary() {
        if (lastToken.chr == '(') {
            return parseParentExp();
        }
        else if (lastToken.type == tok_identifier) {
            return parseIdentifierExp();
        }
        else if (lastToken.type == tok_number) {
            return parseNumberExp();
        }
        else if (lastToken.type == tok_string) {
            return parseStringExp();
        }
        return nil;
    }
    
    QYExpression* parseExp() {
        QYExpression *leftExp = parsePrimary();
        //三目运算符
        if (lastToken.chr == '?') {
            getNextToken();
            QYExpression *trueExp = parsePrimary();
            if (lastToken.chr != ':') {
                throw "三目运算符错误";
            }
            //略过 :
            getNextToken();
            QYExpression *falseExp = parsePrimary();
            return new QYQuestionExpression(leftExp, trueExp, falseExp);
        }
        //加减乘除等
        else if (getOptPrec(OPERATOR(lastToken.chr)) != 0){
            return parseBinaryExpression(leftExp, (OPERATOR)lastToken.chr);
        }
        return leftExp;
    }
    
    /// 获得运算符优先级
    int getOptPrec(OPERATOR Opt) {
        switch(Opt) {
            case opt_none:
                return 0;
            case opt_add:
                return 10;
            case opt_sub:
                return 10;
            case opt_mul:
                return 20;
            case opt_div:
                return 20;
        }
        
        return 0;
    }
    
    /// left + cur * right 左边的运算符小于右边的，递归，把右边 cur * right，作为一个表达式返回
    /// left * cur + right 左边的运算符大于右边的，返回当前表示式
    /// left + cur + right 左边的运算符等于右边的，返回当前表达式
    /// - Parameters:
    ///   - leftExp: 左边的运算符，上面例子中的xx
    ///   - leftOpt: 左边表达式左边的运算符
    QYExpression* parseBinaryExpression(QYExpression *leftExp, OPERATOR leftOpt) {
        //进入后当前的是 leftOpt
        int leftPrec = getOptPrec(leftOpt);
        //略过左边运算符
        getNextToken();
        // curExp
        QYExpression *curExp = parsePrimary();
        //rightOpt
        OPERATOR rightOpt = (OPERATOR)lastToken.chr;
        int rightPrec = getOptPrec(rightOpt);
        
        //右边没有运算符
        if (rightPrec <= 0) {
            return new QYBinaryExpression(leftExp, curExp, leftOpt);
        }
        //右边优先级小于左边
        else if (rightPrec <= leftPrec) {
            return parseBinaryExpression(new QYBinaryExpression(leftExp, curExp, leftOpt), rightOpt);
        }
        
        //右边优先级大于左边, 把cur [opt] right 作为rightExp返回
        QYExpression *rightExp = parseBinaryExpression(curExp, rightOpt);
        return new QYBinaryExpression(leftExp, rightExp, leftOpt);
    }
    
    QYNumberExpression* parseNumberExp() {
        //确定当前是数字了
        QYNumberExpression *numExp = new QYNumberExpression(lastToken.number);
        getNextToken();
        return numExp;
    }
    
    QYStringExpression* parseStringExp() {
        QYStringExpression *strExp = new QYStringExpression(lastToken.identifier);
        getNextToken();
        return strExp;
    }
    
    //  ()的情况，当lastToken.chr确定是(时调用
    QYExpression* parseParentExp() {
        //略过(
        getNextToken();
        //处理完()内的表达式
        QYExpression *exp = parseExp();//TODO:返回个值
        if (lastToken.chr != ')') {
            throw "()表达式内错误";
        }
        //略过)
        getNextToken();
        //TODO:返回个值
        return exp;
    }

    //变量或者方法调用
    //比如 a.b()[3]().c，parseIdentifierExp代表开始解析第一个标识符，因为第一个是调用者，没有其他调用者
    //_parseIdentifierExp代表已经不是第一个标识符了
    QYExpression *parseIdentifierExp() {
        std::string identifier = lastToken.identifier;
        getNextToken();
        return _parseIdentifierExp(new QYIdentifierExpression(identifier));
    }
    
    QYExpression *_parseIdentifierExp(QYExpression *callee) {
        QYExpression *expression = nullptr;
        //确定是方法调用了
        if (lastToken.chr == '(') {
            //TODO:返回个值
            expression = parseFunctionCallExp(callee);
        }
        //确定是属性访问
        else if (lastToken.chr == '.') {
            //TODO:返回个值
            expression = parsePropertyCallExp(callee);
        }
        //确定是数组访问
        else if (lastToken.chr == '[') {
            //TODO:返回个值
            expression = parseArrayAccessExp(callee);
        }
        //都不是，那就暂定变量了，后面有其他情况再加
        else {
            //TODO:返回个值
        }

        int curChar = lastToken.chr;
        if (curChar == '.' || curChar == '[' || curChar == '(' ) {
            _parseIdentifierExp(expression);
        }
        return expression;
    }

    
    
    
    QYFunctionExpression* parseFunctionCallExp(QYExpression *val) {
        //当前是(
        getNextToken();
        std::vector<QYExpression *> args;
        //如果有参数
        if(lastToken.chr != ')') {
            while(true) {
                QYExpression *arg = parseExp();
                if (!arg) {
                    throw "方法参数解析错误";
                }
                args.push_back(arg);
                //调用结束
                if (lastToken.chr == ')') {
                    break;
                }
                //还有参数，这里应该是, 不然就报错
                else if (lastToken.chr != ',') {
                    throw "方法调用参数错误";
                }
                //继续读取参数
                getNextToken();
            }
        }
        QYFunctionExpression *funcExp = new QYFunctionExpression(val, args);
        //略过)
        getNextToken();
        return funcExp;
    }
    
    QYPropertyAccessExpression* parsePropertyCallExp(QYExpression *callee) {
        //当前是.，获取下一个token
        getNextToken();
        if (lastToken.type != tok_identifier) {
            throw ".调用错误，不是标识符";
        }
        QYPropertyAccessExpression *propertyExp = new QYPropertyAccessExpression(callee, lastToken.identifier);
        getNextToken();
        return propertyExp;
    }
    
    QYCollectionAccessExpression* parseArrayAccessExp(QYExpression *callee) {
        //当前是[，略过
        getNextToken();
        //解析[]中的表达式
        QYExpression *index = parseExp();
        QYCollectionAccessExpression *collectionExp = new QYCollectionAccessExpression(callee, index);
        //略过]
        getNextToken();
        return collectionExp;
    }
    
};




void printNumber(char *src) {
    QYTokenParser parser(src);
    QYBinaryExpression *exp = (QYBinaryExpression *)parser.parseExp();
    printf("%s = %lf\n", src, exp->getNumberValue());
}

void testNumberOpt() {
    printNumber(" 0 ");
    printNumber("  1 + 2 ");
    printNumber("  1 - 2 ");
    printNumber("  99 * 100 ");
    printNumber("  99 /3 ");
    printNumber(" 1+2 * 3 + 4 /2 + (3 * 6)/2  ");
}


int main(int argc, const char * argv[]) {
    testNumberOpt();
    return 0;
}
