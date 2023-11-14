//
//  QYQuestionExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#ifndef QYQuestionExpression_hpp
#define QYQuestionExpression_hpp

#include <stdio.h>
#include "QYExpression.h"
class QYQuestionExpression : public QYExpression {
public:
    QYQuestionExpression(QYExpression *questionExp, QYExpression *trueExp, QYExpression *falseExp);
    virtual double getNumberValue(QYExpressionContext *expContext) override;
    virtual std::string getStringValue(QYExpressionContext *expContext) override;
    virtual bool getBoolValue(QYExpressionContext *expContext) override;

private:
    QYExpression *mQuestionExp;
    QYExpression *mTrueExp;
    QYExpression *mFalseExp;
    bool getQuestionBool(QYExpressionContext *expContext);
};

#endif /* QYQuestionExpression_hpp */
