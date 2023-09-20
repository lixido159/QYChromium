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
    tok_identifier = 1,//文本
    tok_number = 2,//数字
};

#include <string>


class QYExpression {
    
};

class QYNumberExpression : public QYExpression {
public:
    QYNumberExpression(double number):mNumber(number){};
    double mNumber;
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


struct QYToken {
    TOKEN_TYPE type;
    std::string identifier;
    double number;
};


//
class QYTokenParser {
public:
    std::string src;
    int curIndex = 0;
    int lastChar = ' ';
    QYToken currentToken;
    
    int getChar() {
        return src[curIndex++];
    }
    
    int currentChar() {
        return src[curIndex];
    }
    
    QYToken getNextToken() {
        while(isspace(lastChar)) {
            lastChar = getChar();
        }
        //字母开头
        if (isalpha(lastChar)) {
            std::string identifier = std::to_string(lastChar);
            while(isalnum(lastChar = getChar())) {
                identifier += lastChar;
            }
            currentToken = {tok_identifier, identifier, 0};
            return currentToken;
            
        }
        //数字开头
        if (isdigit(lastChar)) {
            std::string numberStr = std::to_string(lastChar);
            while(isnumber(lastChar = getChar()) || lastChar == '.') {
                numberStr += lastChar;
            }
            currentToken = {tok_number, nullptr, strtod(numberStr.c_str(), nullptr)};
            return currentToken;
        }
        currentToken = {tok_other, nullptr, 0};
        return currentToken;
    };
    
    QYExpression* parseExp() {
        
    }
    
    QYNumberExpression* parseNumberExp() {
        //确定当前是数字了
        QYNumberExpression *numExp = new QYNumberExpression(currentToken.number);
        getNextToken();
        return numExp;
    }
    
    QYStringExpression* parseStringExp() {
        //当前是"或'
        int quote = currentChar();
        getNextToken();
        std::string str;
        //遇到转义字符
        bool hasEscapeChar = false;
        while(true) {
            //上一个是转义字符
            if (hasEscapeChar) {
                hasEscapeChar = false;
                str.push_back(currentChar());
            }
            //遇到转义字符
            else if (currentChar() == '\\') {
                hasEscapeChar = true;
            }
            //结束
            else if (currentChar() == quote) {
                getNextToken();
                break;
            } else {
                str.push_back(currentChar());
            }
            getNextToken();
        }
        QYStringExpression *strExp = new QYStringExpression(str);
        return strExp;
    }
    
    //  ()的情况，当currentChar确定是(时调用
    QYExpression* parseParentExp() {
        //略过(
        getNextToken();
        //处理完()内的表达式
        parseExp();//TODO:返回个值
        if (currentChar() != ')') {
            throw "()表达式内错误";
        }
        //略过)
        getNextToken();
        //TODO:返回个值
    }

//    a.b()[3]().c
    //变量或者方法调用
    QYExpression *parseIdentifierExp(QYExpression *callee) {
        std::string identifier = currentToken.identifier;
        getNextToken();
        return _parseIdentifierExp(new QYIdentifierExpression(identifier));
    }
    
    QYExpression *_parseIdentifierExp(QYExpression *callee) {
        QYExpression *expression = nullptr;
        //确定是方法调用了
        if (currentChar() == '(') {
            //TODO:返回个值
            expression = parseFunctionCallExp(callee);
        }
        //确定是属性访问
        else if (currentChar() == '.') {
            //TODO:返回个值
            expression = parsePropertyCallExp(callee);
        }
        //确定是数组访问
        else if (currentChar() == '[') {
            //TODO:返回个值
            expression = parseArrayAccessExp(callee);
        }
        //都不是，那就暂定变量了，后面有其他情况再加
        else {
            //TODO:返回个值
        }

        int curChar = currentChar();
        if (curChar == '.' || curChar == '[' || curChar == '(' ) {
            parseIdentifierExp(expression);
        }
        return expression;
    }

    
    
    
    QYFunctionExpression* parseFunctionCallExp(QYExpression *val) {
        //当前是(
        getNextToken();
        std::vector<QYExpression *> args;
        //如果有参数
        if(currentChar() != ')') {
            while(true) {
                QYExpression *arg = parseExp();
                if (!arg) {
                    throw "方法参数解析错误";
                }
                args.push_back(arg);
                //调用结束
                if (currentChar() == ')') {
                    break;
                }
                //还有参数，这里应该是, 不然就报错
                else if (currentChar() != ',') {
                    throw "方法调用参数错误";
                }
                //继续读取参数
                getNextToken();
            }
        }
        QYFunctionExpression *funcExp = new QYFunctionExpression(val, args);
        //略过)
        getNextToken();
    }
    
    QYPropertyAccessExpression* parsePropertyCallExp(QYExpression *callee) {
        //当前是.，获取下一个token
        getNextToken();
        if (currentToken.type != tok_identifier) {
            throw ".调用错误，不是标识符";
        }
        QYPropertyAccessExpression *propertyExp = new QYPropertyAccessExpression(callee, currentToken.identifier);
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





int main(int argc, const char * argv[]) {
    
    return 0;
}

