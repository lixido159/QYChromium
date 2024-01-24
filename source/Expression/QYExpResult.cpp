//
//  QYExpResult.cpp
//  QYView
//
//  Created by yinquan on 2024/1/23.
//

#include "QYExpResult.h"


QYExpResult::QYExpResult(QYExpResultType _type, std::string _string): type(_type), string(_string)  {
    
}

QYExpResult::QYExpResult(QYExpResultType _type, double _number): type(_type), number(_number) {
    
}

QYExpResult::QYExpResult(QYExpResultType _type, bool _boolean): type(_type), boolean(_boolean) {
    
}
