//
//  QYContextJSValue.hpp
//  QYView
//
//  Created by yinquan on 2023/12/4.
//

#ifndef QYContextJSValue_hpp
#define QYContextJSValue_hpp

#include <stdio.h>
#include "CommonHeader.h"
#include "QYJSValue.h"
#include "IQYExpDataContext.h"
class QYPageCompContext;
//这是js里的QYJSContext对象
class QYContextJSValue: public IQYExpDataContext {
public:
    QYContextJSValue(std::weak_ptr<QYPageCompContext> pageCompContext);
    
    std::map<std::string, QYJSValue *> getDataMap();
    QYJSValue *getValue();
    QYJSValue *getDataValue();

    virtual bool getBoolForKey(std::string key) override;
    virtual std::string getStringForKey(std::string key) override;
    virtual double getNumberForKey(std::string key) override;

private:
    std::weak_ptr<QYPageCompContext> mPageCompContext;
    std::unique_ptr<QYJSValue> mContextObjectValue;
    //data设置的value
    std::map<std::string, QYJSValue *> mDataMap;
    
    void registerDataInterface();

};

#endif /* QYContextJSValue_hpp */
