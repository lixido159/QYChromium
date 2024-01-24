//
//  QYToken.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYToken.h"
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
        case opt_rem:
            return 20;
        case opt_eql:
            return 5;
        case opt_and:
            return 5;
        case opt_or:
            return 5;
    }
    
    return 0;
}



//opt_add = 1,// +
//opt_addEql = 2,// +=
//opt_sub = 3,// -
//opt_subEql = 4,// -=
//opt_mul = 5,// *
//opt_mulEql = 6,// *=
//opt_div = 7,//除 /
//opt_divEql = 8,//除 /
//opt_eql = 9,//比较 ==
//opt_not = 10, // !
//opt_notEql = 11, // !=
//opt_and = 12, // &&
//opt_rem = 13, // &
//opt_or = 14, // ||

//QYExpResult add(QYExpression *first, QYExpression *second) {
//    
//}
//
//QYExpResult sub(QYExpression *first, QYExpression *second) {
//    
//}
//
//QYExpResult mul(QYExpression *first, QYExpression *second) {
//    
//}
//
//QYExpResult div(QYExpression *first, QYExpression *second) {
//    
//}
//
//QYExpResult eql(QYExpression *first, QYExpression *second) {
//    
//}
//
//QYExpResult notEql(QYExpression *first, QYExpression *second) {
//    
//}
//
//QYExpResult AND(QYExpression *first, QYExpression *second) {
//    
//}
//
//QYExpResult rem(QYExpression *first, QYExpression *second) {
//    
//}
//
//QYExpResult OR(QYExpression *first, QYExpression *second) {
//    
//}
//QYExpResult calculateBinaryExp(QYExpression *first, QYExpression *second, OPERATOR opt) {
//    switch (opt) {
//        case opt_add:
//            return add(first, second);
//        case opt_sub:
//            return sub(first, second);
//        case opt_mul:
//            return mul(first, second);
//        case opt_div:
//            return div(first, second);
//        case opt_eql:
//            return eql(first, second);
//        case opt_notEql:
//            return notEql(first, second);
//        case opt_and:
//            return AND(first, second);
//        case opt_rem:
//            return rem(first, second);
//        case opt_or:
//            return OR(first, second);
//        default:
//            throw "unknown Operator";
//            break;
//    }
//}
