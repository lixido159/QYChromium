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

class QYPropertyFinalValue {
public:
    enum Type {
        Null,
        Number,
        String,
        Bool
    };
    
    ~QYPropertyFinalValue() {
        
    }

    QYPropertyFinalValue(double value) {
        mType = QYPropertyFinalValue::Number;
        mNumber = value;
    }
    QYPropertyFinalValue(std::string value) {
        mType = QYPropertyFinalValue::String;
        mString = value;
    }
    QYPropertyFinalValue(bool value) {
        mType = QYPropertyFinalValue::Bool;
        mBool = value;
    }
    double getNumberValue() {
        return mNumber;
    }
    std::string getStringValue() {
        return mString;
    }
    bool getBoolValue() {
        return mBool;
    }

private:
    union {
        double mNumber;
        std::string mString;
        bool mBool;
    };
    Type mType;
};

class QYPropertyValue : public IQYExpressionContextObserver, public std::enable_shared_from_this<QYPropertyValue>{
public:
    QYPropertyValue(std::string key, std::string src, std::shared_ptr<QYPageCompContext> dataContext);
    ~QYPropertyValue();
    double getNumberValue();
    std::string getStringValue();
    bool getBoolValue();
    
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
