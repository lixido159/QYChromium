//
//  QYFunction.h
//  QYView
//
//  Created by yinquan on 2023/8/23.
//

#ifndef QYFunction_h
#define QYFunction_h
#include "v8.h"
class QYJSValue;
class QYJSContext;
using QYFunctionType = std::function<QYJSValue *(QYJSContext *, QYJSValue*)>;

struct QYFunction {
    QYFunctionType func;
    QYJSContext *jsContext;
};
#endif /* QYFunction_h */
