//
//  QYPropertySetter.cpp
//  QYView
//
//  Created by yinquan on 2023/10/12.
//

#include "QYPropertySetter.h"

QY_Color strToColor(std::string str) {
    if (str == "red") {
        return {255, 0, 0, 255};
    } else if (str == "black") {
        return {0, 0, 0, 255};
    } else if (str == "green") {
        return {0, 255, 0, 255};
    } else if (str == "blue") {
        return {0, 0, 255, 255};
    } else if (str == "yellow") {
        return {255, 255, 0, 255};
    } else if (str == "gray") {
        return {128, 128, 128, 255};
    } else {
        return {255, 255, 255, 255};
    }
}

bool proptyFunc_View_BackgroundColor(IQYBaseView *view, QYPropertyValue *propValue) {
    view->setBackgroundColor(strToColor(propValue->getStringValue().c_str()));
    return false;
};

bool proptyFunc_View_Left(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    YGValue value = YGNodeStyleGetPosition(node, YGEdgeLeft);
    if (value.unit == YGUnitPoint && value.value == propValue->getNumberValue()) {
        return false;
    }
    YGNodeStyleSetPosition(node, YGEdgeLeft, propValue->getNumberValue());
    return true;
};

bool proptyFunc_View_Top(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    YGValue value = YGNodeStyleGetPosition(node, YGEdgeTop);
    if (value.unit == YGUnitPoint && value.value == propValue->getNumberValue()) {
        return false;
    }
    YGNodeStyleSetPosition(node, YGEdgeTop, propValue->getNumberValue());
    return true;
};

bool proptyFunc_View_Height(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    YGNodeStyleSetHeight(node, propValue->getNumberValue());
    return true;
};

bool proptyFunc_View_Width(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    YGNodeStyleSetWidth(node, propValue->getNumberValue());
    return true;
};


//在这里新增属性方法
QYPropertySetter::QYPropertySetter() {
    mPropFuncMap.insert(std::pair("background-color", &proptyFunc_View_BackgroundColor));
    mPropFuncMap.insert(std::pair("width", &proptyFunc_View_Width));
    mPropFuncMap.insert(std::pair("height", &proptyFunc_View_Height));
    mPropFuncMap.insert(std::pair("top", &proptyFunc_View_Top));
    mPropFuncMap.insert(std::pair("left", &proptyFunc_View_Left));
}


void QYPropertySetter::setProperty(IQYBaseView *view, QYPropertyValue *proptyValue, bool noLayout) {
    bool needLayout = false;
    if (mPropFuncMap.find(proptyValue->getKey()) != mPropFuncMap.end()) {
        needLayout = mPropFuncMap[proptyValue->getKey()](view, proptyValue);
    }
    if (needLayout && !noLayout) {
        view->requestLayout();
    }
}

