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
    virtual double getNumberValue(IQYExpressionContext *expContext) override;
    virtual std::string getStringValue(IQYExpressionContext *expContext) override;
    virtual bool getBoolValue(IQYExpressionContext *expContext) override;

private:
    QYExpression *mQuestionExp;
    QYExpression *mTrueExp;
    QYExpression *mFalseExp;
    bool getQuestionBool(IQYExpressionContext *expContext);
};

#endif /* QYQuestionExpression_hpp */
