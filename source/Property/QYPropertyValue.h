//
//  QYPropertyValue.hpp
//  QYView
//
//  Created by yinquan on 2023/10/11.
//

#ifndef QYPropertyValue_hpp
#define QYPropertyValue_hpp
#include "QYExpression.h"
#include "IQYPropertyValueObserver.h"
#include "QYPageCompContext.h"
#include <stdio.h>
#include "QYExpressionContext.h"
#include "QYPropertyFinalValue.h"


class QYPropertyValue : public IQYExpressionContextObserver, public std::enable_shared_from_this<QYPropertyValue>{
public:
    QYPropertyValue(std::string key, std::string src, std::shared_ptr<QYPageCompContext> dataContext);
    ~QYPropertyValue();
    double getNumberValue();
    std::string getStringValue();
    bool getBoolValue();
    
    std::string getSrc();
    std::string getKey();
    void setObserver(IQYPropertyValueObserver *observer);
    void onDataUpdate();
public://IQYExpressionContextObserver
    virtual void expContextQueryKey(std::string key) override;
private:
    QYExpression *parseSrc(std::string src);
    void clear();
    //缓存计算的结果
    std::unique_ptr<QYPropertyFinalValue> mFinalValue = nullptr;
    std::string mSrc = "";
    std::string mKey = "";
    QYExpression *mExp = nullptr;
    std::shared_ptr<QYPageCompContext> mDataContext = nullptr;
    IQYPropertyValueObserver *mObserver;
};


#endif /* QYPropertyValue_hpp */
