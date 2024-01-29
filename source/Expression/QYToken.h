//
//  QYToken.hpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#ifndef QYToken_hpp
#define QYToken_hpp

#include <stdio.h>
#include <string>
class QYExpression;
enum TOKEN_TYPE {
    tok_other = -1,//其他
    tok_eof = 0,//结束
    tok_identifier = 1,//标识符
    tok_number = 2,//数字
    tok_string = 3,//字符串 ""  ''
    tok_operator = 4,//运算符
};

enum OPERATOR {
    opt_none = 0,
    opt_add = 1,// +
    opt_addEql = 2,// +=
    opt_sub = 3,// -
    opt_subEql = 4,// -=
    opt_mul = 5,// *
    opt_mulEql = 6,// *=
    opt_div = 7,//除 /
    opt_divEql = 8,//除 /=
    opt_eql = 9,//比较 ==
    opt_not = 10, // !
    opt_notEql = 11, // !=
    opt_and = 12, // &&
    opt_rem = 13, // %
    opt_or = 14, // ||
};

struct QYToken {
    TOKEN_TYPE type;
    std::string identifier;
    double number;
    int chr;
};

int getOptPrec(OPERATOR Opt);




#endif /* QYToken_hpp */
