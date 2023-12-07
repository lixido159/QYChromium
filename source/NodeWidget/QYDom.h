//
//  QYDom.hpp
//  QYView
//
//  Created by yinquan on 2023/12/7.
//

#ifndef QYDom_hpp
#define QYDom_hpp

#include <stdio.h>
#include "QYBaseWidget.h"
#include "QYJSValue.h"
//Dom
class QYDom {
public:
    QYDom(std::shared_ptr<QYBaseWidget> widget);
    QYJSValue *getValue();
private:
    void registerDomValueInterface();
    std::shared_ptr<QYBaseWidget> mWidget;
    //dom jsvalue
    std::unique_ptr<QYJSValue> mJSValue;
};


#endif /* QYDom_hpp */
