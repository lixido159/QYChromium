//
//  QYExpResult.hpp
//  QYView
//
//  Created by yinquan on 2024/1/23.
//

#ifndef QYExpResult_hpp
#define QYExpResult_hpp

#include <stdio.h>
#include <string>

enum class QYExpResultType {
    None,
    Number,
    String,
    Boolean,
    Object,
};
class QYExpResult {
    QYExpResultType type;
    std::string string;
    double number;
    bool boolean;

    QYExpResult(QYExpResultType _type, std::string _string);
    QYExpResult(QYExpResultType _type, double _number);
    QYExpResult(QYExpResultType _type, bool _boolean);
};


#endif /* QYExpResult_hpp */
