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
    virtual double getNumberValue() override;
    virtual std::string getStringValue() override;
    virtual bool getBoolValue() override;

private:
    QYExpression *mQuestionExp;
    QYExpression *mTrueExp;
    QYExpression *mFalseExp;
    bool getQuestionBool();
};

#endif /* QYQuestionExpression_hpp */
