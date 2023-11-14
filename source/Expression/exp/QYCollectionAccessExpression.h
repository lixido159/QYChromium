//
//  QYCollectionAccessExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#ifndef QYCollectionAccessExpression_hpp
#define QYCollectionAccessExpression_hpp

#include <stdio.h>
#include "QYExpression.h"
class QYCollectionAccessExpression : public QYExpression{
public:
    QYCollectionAccessExpression(QYExpression *callee, QYExpression *index): mCallee(callee), mIndex(index){};
    QYExpression *mCallee;
    //数组、字典都有可能
    QYExpression *mIndex;
    virtual double getNumberValue(IQYExpressionContext *expContext) override {
        return 0;
    }
    
    virtual std::string getStringValue(IQYExpressionContext *expContext) override {
        return "";
    }
    
    virtual bool getBoolValue(IQYExpressionContext *expContext) override {
        return false;
    }
};

#endif /* QYCollectionAccessExpression_hpp */
