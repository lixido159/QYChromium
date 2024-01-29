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

class QYExpressionParser {
public:
    QYExpressionParser(std::string str);
    std::shared_ptr<QYExpression> parseExp();

private:
    std::string mSrc;
    bool mIsMustache = false;
    int mCurIndex = -1;
    //最新所指
    int mCurrentChar = ' ';
    //lastToken代表当前解析出来的token：字符串、数字、标识符、其他字符
    //currentChar代表token的下一个字符，最新位置的char
    QYToken mLastToken;

private:
    int getNextChar();
    int getCurrentInt();
    void passSpace();
    QYToken getNextIdentifier();
    QYToken getNextNumber();
    QYToken getNextString();
    QYToken getNextOperator();
    QYToken getNextToken();
    
    std::shared_ptr<QYExpression> parsePrimary();
    std::shared_ptr<QYExpression> parseBinaryExpression(std::shared_ptr<QYExpression>leftExp, OPERATOR leftOpt);
    std::shared_ptr<QYExpression> parseNumberExp();
    std::shared_ptr<QYExpression> parseStringExp();
    std::shared_ptr<QYExpression> parseParentExp();
    std::shared_ptr<QYExpression> parseIdentifierExp();
    std::shared_ptr<QYExpression> _parseIdentifierExp(std::shared_ptr<QYExpression>callee);
    std::shared_ptr<QYExpression> parseFunctionCallExp(std::shared_ptr<QYExpression>val);
    std::shared_ptr<QYExpression> parsePropertyCallExp(std::shared_ptr<QYExpression>callee);
    std::shared_ptr<QYExpression> parseArrayAccessExp(std::shared_ptr<QYExpression>callee);
    std::shared_ptr<QYExpression> parseUnaryExp();
};


#endif /* QYExpressionParser_hpp */
