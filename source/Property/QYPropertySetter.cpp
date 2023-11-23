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

void proptyFunc_View_BackgroundColor(IQYBaseView *view, QYPropertyValue *propValue) {
    view->setBackgroundColor(strToColor(propValue->getStringValue().c_str()));
};

void proptyFunc_View_Left(IQYBaseView *view, QYPropertyValue *propValue) {
    view->setX(propValue->getNumberValue());
};

void proptyFunc_View_Top(IQYBaseView *view, QYPropertyValue *propValue) {
    view->setY(propValue->getNumberValue());
};

void proptyFunc_View_Height(IQYBaseView *view, QYPropertyValue *propValue) {
    view->setHeight(propValue->getNumberValue());
};

void proptyFunc_View_Width(IQYBaseView *view, QYPropertyValue *propValue) {
    view->setWidth(propValue->getNumberValue());
};


//在这里新增属性方法
QYPropertySetter::QYPropertySetter() {
    mPropFuncMap.insert(std::pair("background-color", &proptyFunc_View_BackgroundColor));
    mPropFuncMap.insert(std::pair("width", &proptyFunc_View_Width));
    mPropFuncMap.insert(std::pair("height", &proptyFunc_View_Height));
    mPropFuncMap.insert(std::pair("top", &proptyFunc_View_Top));
    mPropFuncMap.insert(std::pair("left", &proptyFunc_View_Left));
}


void QYPropertySetter::setProperty(IQYBaseView *view, QYPropertyValue *proptyValue) {
    if (mPropFuncMap.find(proptyValue->getKey()) != mPropFuncMap.end()) {
        mPropFuncMap[proptyValue->getKey()](view, proptyValue);
    }
}

