//
//  QYExpressionParser.hpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#ifndef QYExpressionParser_hpp
#define QYExpressionParser_hpp

#include <stdio.h>
#include "QYExpression.h"
#include "QYToken.h"
#include "QYExpressionContext.h"

class QYExpressionParser {
public:
    QYExpressionParser(std::string str);
    QYExpression* parseExp();

private:
    std::string mSrc;
    bool mIsMustache = false;
    int mCurIndex = -1;
    //只能在getNextToken时使用
    int mCurrentChar = ' ';
    //lastToken代表当前解析出来的token：字符串、数字、标识符、其他字符
    //currentChar代表token的下一个字符，最新位置的char
    QYToken mLastToken;

private:
    int getNextChar();
    int getCurrentInt();
    int getCurrentChar();
    void passSpace();
    QYToken getNextIdentifier();
    QYToken getNextNumber();
    QYToken getNextString();
    QYToken getNextToken();
    
    QYExpression* parsePrimary();
    QYExpression* parseBinaryExpression(QYExpression *leftExp, OPERATOR leftOpt);
    QYExpression* parseNumberExp();
    QYExpression* parseStringExp();
    QYExpression* parseParentExp();
    QYExpression *parseIdentifierExp();
    QYExpression *_parseIdentifierExp(QYExpression *callee);
    QYExpression* parseFunctionCallExp(QYExpression *val);
    QYExpression* parsePropertyCallExp(QYExpression *callee);
    QYExpression* parseArrayAccessExp(QYExpression *callee);
};


#endif /* QYExpressionParser_hpp */
