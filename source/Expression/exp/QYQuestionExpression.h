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
    QYQuestionExpression(std::shared_ptr<QYExpression> questionExp, std::shared_ptr<QYExpression> trueExp, std::shared_ptr<QYExpression> falseExp);
    virtual QYExpResult getExpResult() override;
private:
    std::shared_ptr<QYExpression> mQuestionExp;
    std::shared_ptr<QYExpression> mTrueExp;
    std::shared_ptr<QYExpression> mFalseExp;
    bool getQuestionBool();
};

#endif /* QYQuestionExpression_hpp */
