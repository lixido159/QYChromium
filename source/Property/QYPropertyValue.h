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
    QYExpResult *getResult();
    
    std::string getSrc();
    std::string getKey();
    void setObserver(IQYPropertyValueObserver *observer);
    void onDataUpdate();
public://IQYExpressionContextObserver
    virtual void expContextQueryKey(std::string key) override;
private:
    std::shared_ptr<QYExpression> parseSrc(std::string src);
    void clear();
    //缓存计算的结果
    QYExpResult mResult;
    std::string mSrc = "";
    std::string mKey = "";
    std::shared_ptr<QYExpression> mExp;
    std::shared_ptr<QYPageCompContext> mDataContext;
    std::shared_ptr<QYExpressionContext> mExpContext;
    IQYPropertyValueObserver *mObserver;
    
    std::shared_ptr<QYExpressionContext> getExpContext();
    std::shared_ptr<QYExpression> getExpression();

};


#endif /* QYPropertyValue_hpp */
