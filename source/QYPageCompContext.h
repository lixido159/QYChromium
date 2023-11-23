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
//让子节点获取Page或Component的属性
class QYPageCompContext : public IQYExpDataContext{
public:
    void addJSKeyObserver(std::string key, std::shared_ptr<QYPropertyValue> observer);
    void notifyDataUpdate(std::string key);
    void registerDataInterface(QYJSValue *dataValue);
    void setPageCompValue(QYJSValue *value);
public://IQYExpressionContext
    virtual bool getBoolForKey(std::string key) override;
    virtual std::string getStringForKey(std::string key) override;
    virtual double getNumberForKey(std::string key) override;
private:
    std::map<std::string, std::vector<std::shared_ptr<QYPropertyValue>>> mObserveProperties;
    
    std::unique_ptr<QYJSValue> mPageCompJSValue;
    std::unique_ptr<QYJSValue> mDataValue;
    std::map<std::string, QYJSValue *> mData;
};

#endif /* QYPageCompContext_hpp */
