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
    opt_add = '+',//加
    opt_sub = '-',//减
    opt_mul = '*',//乘
    opt_div = '/',//除
    opt_eql = 256,//比较
};

struct QYToken {
    TOKEN_TYPE type;
    std::string identifier;
    double number;
    int chr;
};

int getOptPrec(OPERATOR Opt);
#endif /* QYToken_hpp */
