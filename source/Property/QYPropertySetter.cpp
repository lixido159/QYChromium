//
//  QYPropertySetter.cpp
//  QYView
//
//  Created by yinquan on 2023/10/12.
//

#include "QYPropertySetter.h"
#include "QYPropertyCssValueParser.h"
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


#pragma mark - FLEX



bool proptyFunc_View_Flex_Direction(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    YGNodeStyleSetFlexDirection(node, (YGFlexDirection)parseFlexDirectionCssValue(propValue->getStringValue()));
    return true;
};

bool proptyFunc_View_Flex_Wrap(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    return true;
};

bool proptyFunc_View_Flex_Flow(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    return true;
};

bool proptyFunc_View_Justify_Content(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    return true;
};

bool proptyFunc_View_Align_Items(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    YGNodeStyleSetAlignItems(node, (YGAlign)parseAlignItemsCssValue(propValue->getStringValue()));
    return true;
};

bool proptyFunc_View_Align_Content(IQYBaseView *view, QYPropertyValue *propValue) {
    YGNodeRef node = view->getNodeLayout()->getNode();
    return true;
};

//在这里新增属性方法
QYPropertySetter::QYPropertySetter() {
    mPropFuncMap.insert(std::pair("background-color", &proptyFunc_View_BackgroundColor));
    mPropFuncMap.insert(std::pair("width", &proptyFunc_View_Width));
    mPropFuncMap.insert(std::pair("height", &proptyFunc_View_Height));
    mPropFuncMap.insert(std::pair("top", &proptyFunc_View_Top));
    mPropFuncMap.insert(std::pair("left", &proptyFunc_View_Left));
    
    //flex
    mPropFuncMap.insert(std::pair("flex-direction", &proptyFunc_View_Flex_Direction));
    mPropFuncMap.insert(std::pair("flex-wrap", &proptyFunc_View_Flex_Wrap));
    mPropFuncMap.insert(std::pair("flex-flow", &proptyFunc_View_Flex_Flow));
    mPropFuncMap.insert(std::pair("justify-content", &proptyFunc_View_Justify_Content));
    mPropFuncMap.insert(std::pair("align-items", &proptyFunc_View_Align_Items));
    mPropFuncMap.insert(std::pair("align-content", &proptyFunc_View_Align_Content));

    
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

