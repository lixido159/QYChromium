//
//  QYPageCompContext.hpp
//  QYView
//
//  Created by yinquan on 2023/11/9.
//

#ifndef QYPageCompContext_hpp
#define QYPageCompContext_hpp
class QYPropertyValue;
#include <stdio.h>
#include "CommonHeader.h"

//让子节点获取Page或Component的属性
class QYPageCompContext {
public:
    void addProptyObserver(std::weak_ptr<QYPropertyValue> observer);
    void notifyDataUpdate();
private:
    //这里一个变量update后，所有胡子语法属性都要更新，因为你无法确定里面是不是有用到这个变量
    std::vector<std::weak_ptr<QYPropertyValue>> mObserveProperties;

};

#endif /* QYPageCompContext_hpp */
