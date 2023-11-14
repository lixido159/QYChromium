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
    virtual double getNumberValue(QYExpressionContext *expContext) override {
        return 0;
    }
    
    virtual std::string getStringValue(QYExpressionContext *expContext) override {
        return "";
    }
    
    virtual bool getBoolValue(QYExpressionContext *expContext) override {
        return false;
    }
};

#endif /* QYCollectionAccessExpression_hpp */
