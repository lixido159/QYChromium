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

class QYVariableExpression : public QYExpression {
    
};

class QYCallExpression : public QYExpression{
public:
    QYCallExpression(QYExpression *callee):mCallee(callee){}
    QYExpression *mCallee = nullptr;
};

class QYFunctionCallExpression : public QYCallExpression {
public:
    QYFunctionCallExpression(QYExpression *callee, std::string func, std::vector<QYExpression> args): QYCallExpression(callee), mFunc(func), mArgs(args){};
    std::string mFunc;
    std::vector<QYExpression> mArgs;
};

class QYPropertyCallExpression : public QYCallExpression {
public:
    QYPropertyCallExpression(QYExpression *callee, std::string property) : QYCallExpression(callee), mProperty(property){};
    std::string mProperty;
};

class QYArrayCallExpression : public QYCallExpression {
public:
    QYArrayCallExpression(QYExpression *callee, QYExpression *): QYCallExpression(callee), mIndex(index){};
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
        return _parseIdentifierExp(new QYStringExpression(identifier));
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

    
    
    QYNumberExpression* parseNumberExp() {
        //确定当前是数字了
        currentToken.number;
        
        getNextToken();
        //TODO:返回个值
    }
    
    QYFunctionCallExpression* parseFunctionCallExp(QYExpression *callee) {
        //当前是(
        getNextToken();
        //如果有参数
        if(currentChar() != ')') {
            std::vector<QYExpression> args;
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
        QYFunctionCallExpression *funcExp = new QYFunctionCallExpression()
        //略过)
        getNextToken();
    }
    
    QYPropertyCallExpression* parsePropertyCallExp(QYExpression *callee) {
        //当前是.，获取下一个token
        getNextToken();
        if (currentToken.type != tok_identifier) {
            throw ".调用错误，不是标识符";
        }
        QYPropertyCallExpression *propertyExp = new QYPropertyCallExpression(callee, currentToken.identifier);
        getNextToken();
        return propertyExp;
    }
    
    QYArrayCallExpression* parseArrayAccessExp(QYExpression *callee) {
        //当前是[
        getNextToken();
        if (currentToken.type != tok_number) {
            throw "[] 调用错误，不是数字";
        }
        //略过数字
        getNextToken();
        QYExpression *index = parseExp();
        QYArrayCallExpression *arrayExp = new QYArrayCallExpression(callee, index);
        //略过]
        getNextToken();
        return arrayExp;
    }
    
    QYStringExpression* parseStringExp() {
        
    }

    
    QYVariableExpression* parseVariableExp() {
        
    }
};





int main(int argc, const char * argv[]) {
    
    return 0;
}

