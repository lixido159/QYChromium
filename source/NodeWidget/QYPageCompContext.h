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
#include "IQYExpDataContext.h"
#include "QYJSValue.h"
#include "QYContextJSValue.h"


//让子节点获取Page或Component的属性
class QYPageCompContext : public std::enable_shared_from_this<QYPageCompContext> {
public:
    QYPageCompContext(std::shared_ptr<QYJSContext> jsContext);
    void init();
    void addJSKeyObserver(std::string key, std::shared_ptr<IQYPageCompDataObserver> observer);
    void notifyDataUpdate(std::string key);
    void setPageCompValue(QYJSValue *value);
    //js的comp、page对象
    QYJSValue* getPageCompValue();
    //js上下文环境
    std::shared_ptr<QYJSContext> getJSContext();
    //里面持有js里的context对象
    std::shared_ptr<QYContextJSValue> getContextJSValue();
    
private:
    //监听js里setData
    std::map<std::string, std::vector<std::shared_ptr<IQYPageCompDataObserver>>> mDataObservers;
    //qyNative.entry返回的js对象
    std::unique_ptr<QYJSValue> mPageCompJSValue;
    std::shared_ptr<QYJSContext> mJSContext;
    //JS里的context对象
    std::shared_ptr<QYContextJSValue> mContextJSValue;
};

#endif /* QYPageCompContext_hpp */
