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
