//
//  QYExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYExpression.h"
#include <iostream>
#include <sstream>
#include <string>

std::string to_string_precise(double value) {
    std::ostringstream out;
    out << value;
    std::string str = out.str();

    // 删除多余的0和不必要的小数点
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') {
        str.pop_back();
    }

    return str;
}

void QYExpression::setContext(std::shared_ptr<IQYExpDataContext> context) {
    mExpContext = context;
}









