//
//  QYBinaryExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYBinaryExpression.h"


static std::shared_ptr<QYExpResult> add(std::shared_ptr<QYExpressionContext> expContext, std::shared_ptr<QYExpression> leftExp, std::shared_ptr<QYExpression> rightExp) {
    std::shared_ptr<QYExpResult> leftResult = leftExp->getExpResult(expContext);
    std::shared_ptr<QYExpResult> rightResult = rightExp->getExpResult(expContext);
    if (leftResult->isString() || rightResult->isString()) {
        std::string leftStr, rightStr;
        if (leftResult->isNumber()) {
            leftStr = to_string_precise(leftResult->getNumber());
            rightStr = rightResult->getString();
        } else if (rightResult->isNumber()) {
            rightStr = to_string_precise(rightResult->getNumber());
            leftStr = leftResult->getString();
        } else {
            leftStr = leftResult->getString();
            rightStr = rightResult->getString();
        }
        return std::make_shared<QYExpResult>(QYExpResultType::String, leftStr + rightStr);
        
    } else if (leftResult->isNumber() && rightResult->isNumber()) {
        return std::make_shared<QYExpResult>(QYExpResultType::Number, leftResult->getNumber() + rightResult->getNumber());
    }
    throw "add error";
}

static std::shared_ptr<QYExpResult> numberCalculate(std::shared_ptr<QYExpressionContext> expContext, std::shared_ptr<QYExpression> leftExp, std::shared_ptr<QYExpression> rightExp, OPERATOR opt) {
    std::shared_ptr<QYExpResult> leftResult = leftExp->getExpResult(expContext);
    std::shared_ptr<QYExpResult> rightResult = rightExp->getExpResult(expContext);
    double number;
    if (opt == opt_sub) {
        number = leftResult->getNumber() - rightResult->getNumber();
    } else if (opt == opt_mul) {
        number = leftResult->getNumber() * rightResult->getNumber();
    } else if (opt == opt_div) {
        number = leftResult->getNumber() / rightResult->getNumber();
    } else if (opt == opt_rem) {
        number = (int)leftResult->getNumber() % (int)rightResult->getNumber();
    }
    return std::make_shared<QYExpResult>(QYExpResultType::Number, number);
}

static std::shared_ptr<QYExpResult> equalNotEqual(std::shared_ptr<QYExpressionContext> expContext, std::shared_ptr<QYExpression> leftExp, std::shared_ptr<QYExpression> rightExp, bool isEqual) {
    std::shared_ptr<QYExpResult> leftResult = leftExp->getExpResult(expContext);
    std::shared_ptr<QYExpResult> rightResult = rightExp->getExpResult(expContext);
    bool result = false;
    if (leftResult->isString() || rightResult->isString()) {
        std::string leftStr, rightStr;
        if (leftResult->isNumber()) {
            leftStr = to_string_precise(leftResult->getNumber());
            rightStr = rightResult->getString();
        } else if (rightResult->isNumber()) {
            rightStr = to_string_precise(rightResult->getNumber());
            leftStr = leftResult->getString();
        } else {
            leftStr = leftResult->getString();
            rightStr = rightResult->getString();
        }
        result = isEqual ? leftStr.compare(rightStr) == 0 : leftStr.compare(rightStr) != 0;
    } else if (leftResult->isNumber() && rightResult->isNumber()) {
        result = isEqual ? leftResult->getNumber() == rightResult->getNumber() : leftResult->getNumber() != rightResult->getNumber();
    } else if (leftResult->getType() != rightResult->getType()) {
        result = isEqual ? false : true;
    } else {
        result = isEqual ? leftResult->getBoolean() == rightResult->getBoolean() : leftResult->getBoolean() != rightResult->getBoolean();
    }
    return std::make_shared<QYExpResult>(QYExpResultType::Boolean, result);
}

static std::shared_ptr<QYExpResult> andOr(std::shared_ptr<QYExpressionContext> expContext, std::shared_ptr<QYExpression> leftExp, std::shared_ptr<QYExpression> rightExp, bool isAnd) {
    std::shared_ptr<QYExpResult> leftResult = leftExp->getExpResult(expContext);
    std::shared_ptr<QYExpResult> rightResult = rightExp->getExpResult(expContext);
    bool leftBoolean = leftResult->getBoolean();
    bool rightBoolean = rightResult->getBoolean();
    return std::make_shared<QYExpResult>(QYExpResultType::Boolean, isAnd ? (leftBoolean && rightBoolean) : (leftBoolean || rightBoolean));
}

QYBinaryExpression::QYBinaryExpression( std::shared_ptr<QYExpression> leftExp, std::shared_ptr<QYExpression> rightExp, OPERATOR opt):mLeftExp(leftExp), mRightExp(rightExp), mOpt(opt){
     
};


std::shared_ptr<QYExpResult> QYBinaryExpression::getExpResult(std::shared_ptr<QYExpressionContext> expContext) {
    if (mOpt == opt_add) {
        return add(expContext, mLeftExp, mRightExp);
    } else if (mOpt == opt_sub || mOpt == opt_mul || mOpt == opt_div || mOpt == opt_rem) {
        return numberCalculate(expContext, mLeftExp, mRightExp, mOpt);
    } else if (mOpt == opt_eql || mOpt == opt_notEql) {
        return equalNotEqual(expContext, mLeftExp, mRightExp, mOpt == opt_eql);
    } else if (mOpt == opt_and || mOpt == opt_or) {
        return andOr(expContext, mLeftExp, mRightExp, mOpt == opt_and);
    }
    return std::make_shared<QYExpResult>();
}
