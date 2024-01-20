//
//  QYExpressionParser.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYExpressionParser.h"
#include "QYNumberExpression.h"
#include "QYStringExpression.h"
#include "QYIdentifierExpression.h"
#include "QYFunctionExpression.h"
#include "QYPropertyAccessExpression.h"
#include "QYCollectionAccessExpression.h"
#include "QYQuestionExpression.h"
#include "QYBinaryExpression.h"
#include "QYUnaryExpression.h"
const std::string MUSTACHE_START = "{{";
const std::string MUSTACHE_END = "}}";

QYExpressionParser::QYExpressionParser(std::string str):mSrc(str) {
    size_t startIndex = mSrc.find(MUSTACHE_START);
    size_t endIndex = mSrc.find(MUSTACHE_END);
    if (startIndex == std::string::npos || endIndex == std::string::npos) {
        
    } else {
        size_t realStart = startIndex + MUSTACHE_START.length();
        size_t len = endIndex - realStart;
        mSrc = mSrc.substr(realStart, len);
        mIsMustache = true;
        getNextToken();
    }
}

int QYExpressionParser::getNextChar() {
    mCurrentChar = mSrc[++mCurIndex];
    return mCurrentChar;
}

int QYExpressionParser::getCurrentInt() {
    return mCurrentChar - '0';
}




void QYExpressionParser::passSpace() {
    while(isspace(mCurrentChar)) {
        getNextChar();
    }
}

QYToken QYExpressionParser::getNextIdentifier() {
    std::string identifier;
    identifier += mCurrentChar;
    while(isalnum(getNextChar())) {
        identifier += mCurrentChar;
    }
    return {tok_identifier, identifier, 0};
}

QYToken QYExpressionParser::getNextNumber() {
    std::string numberStr = to_string_precise(getCurrentInt());
    while(isnumber(getNextChar()) || mCurrentChar == '.') {
        numberStr += to_string_precise(getCurrentInt());
    }
    return {tok_number, "", strtod(numberStr.c_str(), nullptr)};
}

QYToken QYExpressionParser::getNextString() {
    //单引号还是双引号
    int quote = mCurrentChar;
    std::string str;
    //遇到转义字符
    bool hasEscapeChar = false;
    while(true) {
        //到下一个字符
        getNextChar();
        //上一个是转义字符，这个不管是什么都加上
        if (hasEscapeChar) {
            hasEscapeChar = false;
            str.push_back(mCurrentChar);
        }
        //遇到转义字符
        else if (mCurrentChar == '\\') {
            hasEscapeChar = true;
        }
        //结束
        else if (mCurrentChar == quote) {
            getNextChar();
            break;
        } else {
            str.push_back(mCurrentChar);
        }
    }
    return {tok_string, "", 0};
}

QYToken QYExpressionParser::getNextOperator() {
    char ope = mCurrentChar;
    char next = getNextChar();
    QYToken token;
    if (ope == '+') {
        if (next == '=') {
            token = {tok_operator, "", 0, opt_addEql};
        } else {
            token = {tok_operator, "", 0, opt_add};
        }
    } else if (ope == '-') {
        if (next == '=') {
            token = {tok_operator, "", 0, opt_subEql};
        } else {
            token = {tok_operator, "", 0, opt_sub};
        }
    } else if (ope == '*') {
        if (next == '=') {
            token = {tok_operator, "", 0, opt_mulEql};
        } else {
            token = {tok_operator, "", 0, opt_mul};
        }
    } else if (ope == '/') {
        if (next == '=') {
            token = {tok_operator, "", 0, opt_divEql};
        } else {
            token = {tok_operator, "", 0, opt_div};
        }
    } else if (ope == '!') {
        if (next == '=') {
            token = {tok_operator, "", 0, opt_notEql};
        } else {
            token = {tok_operator, "", 0, opt_not};
        }
    } else if (ope == '=' && next == '=') {
        token = {tok_operator, "", 0, opt_eql};
    } else if (ope == '&') {
        if (next == '&') {
            token = {tok_operator, "", 0, opt_and};
        } else {
            token = {tok_operator, "", 0, opt_rem};
        }
    } else if (ope == '|' && next == '|') {
        token = {tok_operator, "", 0, opt_or};
    } else {
        token = {tok_other, "", 0, ope};
    }
    if (token.type != tok_other) {
        getNextChar();
    }
    return token;
}

QYToken QYExpressionParser::getNextToken() {
    passSpace();
    //字母开头
    if (isalpha(mCurrentChar)) {
        mLastToken = getNextIdentifier();
    }
    //数字开头
    else if (isdigit(mCurrentChar)) {
        mLastToken = getNextNumber();
    }
    else if (mCurrentChar == '\'' || mCurrentChar == '"') {
        mLastToken = getNextString();
    } else if (mCurrentChar == '\0'){
        mLastToken = {tok_eof, "", 0, mCurrentChar};
    }
    //各种符号 + - * / ()等
    else {
        mLastToken = getNextOperator();
    }
    passSpace();
    return mLastToken;
};

//括号、标识符、数字、字符串
//这里代表一个新的解析的开始，它只会解析完一种类型，然后不会继续解析
//parseExp会一直解析
QYExpression* QYExpressionParser::parsePrimary() {
    if (mLastToken.chr == '(') {
        return parseParentExp();
    }
    else if (mLastToken.type == tok_identifier) {
        return parseIdentifierExp();
    }
    else if (mLastToken.type == tok_number) {
        return parseNumberExp();
    }
    else if (mLastToken.type == tok_string) {
        return parseStringExp();
    }
    else if (mLastToken.type == tok_operator) {
        return parseUnaryExp();
    }
    return nullptr;
}

QYExpression* QYExpressionParser::parseExp() {
    //不是胡子语法，整个就是字符串
    if (!mIsMustache) {
        return new QYStringExpression(mSrc);
    }
    QYExpression *leftExp = parsePrimary();
    QYExpression *retExp = leftExp;
    //三目运算符
    if (mLastToken.chr == '?') {
        getNextToken();
        QYExpression *trueExp = parsePrimary();
        if (mLastToken.chr != ':') {
            throw "三目运算符错误";
        }
        //略过 :
        getNextToken();
        QYExpression *falseExp = parsePrimary();
        retExp = new QYQuestionExpression(leftExp, trueExp, falseExp);
    }
    //加减乘除等
    else if (getOptPrec(OPERATOR(mLastToken.chr)) != 0){
        retExp = parseBinaryExpression(leftExp, (OPERATOR)mLastToken.chr);
    }
    return retExp;
}

/// left + cur * right 左边的运算符小于右边的，递归，把右边 cur * right，作为一个表达式返回
/// left * cur + right 左边的运算符大于右边的，返回当前表示式
/// left + cur + right 左边的运算符等于右边的，返回当前表达式
/// - Parameters:
///   - leftExp: 左边的运算符，上面例子中的xx
///   - leftOpt: 左边表达式左边的运算符
QYExpression* QYExpressionParser::parseBinaryExpression(QYExpression *leftExp, OPERATOR leftOpt) {
    //进入后当前的是 leftOpt
    int leftPrec = getOptPrec(leftOpt);
    //略过左边运算符
    getNextToken();
    // curExp
    QYExpression *curExp = parsePrimary();
    //rightOpt
    OPERATOR rightOpt = (OPERATOR)mLastToken.chr;
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

QYExpression* QYExpressionParser::parseNumberExp() {
    //确定当前是数字了
    QYNumberExpression *numExp = new QYNumberExpression(mLastToken.number);
    getNextToken();
    return numExp;
}

QYExpression* QYExpressionParser::parseStringExp() {
    QYStringExpression *strExp = new QYStringExpression(mLastToken.identifier);
    //略过string
    getNextToken();
    return strExp;
}

//  ()的情况，当lastToken.chr确定是(时调用
QYExpression* QYExpressionParser::parseParentExp() {
    //略过(
    getNextToken();
    //处理完()内的表达式
    QYExpression *exp = parseExp();//TODO:返回个值
    if (mLastToken.chr != ')') {
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
QYExpression *QYExpressionParser::parseIdentifierExp() {
    std::string identifier = mLastToken.identifier;
    getNextToken();
    return _parseIdentifierExp(new QYIdentifierExpression(identifier));
}

QYExpression *QYExpressionParser::_parseIdentifierExp(QYExpression *callee) {
    QYExpression *expression = nullptr;
    //确定是方法调用了
    if (mLastToken.chr == '(') {
        //TODO:返回个值
        expression = parseFunctionCallExp(callee);
    }
    //确定是属性访问
    else if (mLastToken.chr == '.') {
        //TODO:返回个值
        expression = parsePropertyCallExp(callee);
    }
    //确定是数组访问
    else if (mLastToken.chr == '[') {
        //TODO:返回个值
        expression = parseArrayAccessExp(callee);
    }
    //都不是，那就暂定变量了，后面有其他情况再加
    else {
        expression = callee;
    }
    
    int curChar = mLastToken.chr;
    if (curChar == '.' || curChar == '[' || curChar == '(' ) {
        _parseIdentifierExp(expression);
    }
    return expression;
}




QYExpression* QYExpressionParser::parseFunctionCallExp(QYExpression *val) {
    //跳过(
    getNextToken();
    std::vector<QYExpression *> args;
    //如果有参数
    if(mLastToken.chr != ')') {
        while(true) {
            QYExpression *arg = parseExp();
            if (!arg) {
                throw "方法参数解析错误";
            }
            args.push_back(arg);
            //调用结束
            if (mLastToken.chr == ')') {
                break;
            }
            //还有参数，这里应该是, 不然就报错
            else if (mLastToken.chr != ',') {
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

QYExpression* QYExpressionParser::parsePropertyCallExp(QYExpression *callee) {
    //当前是.，获取下一个token
    getNextToken();
    if (mLastToken.type != tok_identifier) {
        throw ".调用错误，不是标识符";
    }
    QYPropertyAccessExpression *propertyExp = new QYPropertyAccessExpression(callee, mLastToken.identifier);
    getNextToken();
    return propertyExp;
}

QYExpression* QYExpressionParser::parseArrayAccessExp(QYExpression *callee) {
    //当前是[，略过
    getNextToken();
    //解析[]中的表达式
    QYExpression *index = parseExp();
    QYCollectionAccessExpression *collectionExp = new QYCollectionAccessExpression(callee, index);
    //略过]
    getNextToken();
    return collectionExp;
}

QYExpression* QYExpressionParser::parseUnaryExp() {
    int opt = mLastToken.chr;
    getNextToken();
    QYExpression *exp = parsePrimary();
    return new QYUnaryExpression(exp, (OPERATOR)opt);
}


