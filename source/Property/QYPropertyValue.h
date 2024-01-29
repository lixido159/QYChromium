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
#include "QYPropertyFinalValue.h"


class QYPropertyValue : public std::enable_shared_from_this<QYPropertyValue> , public IQYPageCompDataObserver, public IQYExpressionContextObserver {
public:
    QYPropertyValue(std::string key, std::string src, std::shared_ptr<QYPageCompContext> pageCompContext);
    ~QYPropertyValue();
    std::shared_ptr<QYExpResult> getResult();
    
    std::string getSrc();
    std::string getKey();
    void setObserver(IQYPropertyValueObserver *observer);
    virtual void onDataUpdate(std::string key) override;
    virtual void expContextQueryKey(std::string key) override;

private:
    std::shared_ptr<QYExpression> parseSrc(std::string src);
    void clear();
    //缓存计算的结果
    std::shared_ptr<QYExpResult> mResult;
    std::string mSrc = "";
    std::string mKey = "";
    std::shared_ptr<QYExpression> mExp;
    std::shared_ptr<QYPageCompContext> mPageCompContext;
    IQYPropertyValueObserver *mObserver;
    
    std::shared_ptr<QYExpression> getExpression();

};


#endif /* QYPropertyValue_hpp */
