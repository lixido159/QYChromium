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
    }
    
    return 0;
}
