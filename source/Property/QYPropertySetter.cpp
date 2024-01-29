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
    view->setBackgroundColor(strToColor(propValue->getResult()->getString().c_str()));
    return false;
};

bool proptyFunc_View_Left(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setLeft(YGPointValue(propValue->getResult()->getNumber()));
    return true;
};

bool proptyFunc_View_Top(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setTop(YGPointValue(propValue->getResult()->getNumber()));
    return true;
};

bool proptyFunc_View_Height(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setHeight(parseNumberStringToYGValue(propValue->getResult()->getString()));
    return true;
};

bool proptyFunc_View_Width(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setWidth(parseNumberStringToYGValue(propValue->getResult()->getString()));
    return true;
};


#pragma mark - FLEX
bool proptyFunc_View_Display(IQYBaseView *view, QYPropertyValue *propValue) {
    YGDisplay display = propValue->getResult()->getString().compare("flex") == 0 ? YGDisplayFlex : YGDisplayNone;
    view->getNodeLayout()->setDisplay(display);
    return true;
};


//子元素排列的主轴
//row:从左往右
//column: 从上往下
bool proptyFunc_View_Flex_Direction(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setFlexDirection(parseFlexDirectionCssValue(propValue->getResult()->getString()));
    return true;
};

bool proptyFunc_View_Flex_Wrap(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setFlexWrap(parseFlexWrapCssValue(propValue->getResult()->getString()));
    return true;
};

//子元素在主轴对齐方式
//flex-start（默认值）：左对齐
//flex-end：右对齐
//center：居中
//space-between：两端对齐，项目之间间隔相等；
//space-around：每个项目两侧的间隔相等，即项目之间的间隔比项目与边框的间隔大一倍
//space-evenly: 间距相等
bool proptyFunc_View_Justify_Content(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setJustifyContent(parseJustifyContentCssValue(propValue->getResult()->getString()));
    return true;
};

//子元素在交叉轴对齐方式，flex-wrap设置为后不生效
//flex-start：起点对齐；
//flex-end：终点对齐；
//center：中点对齐
//baseline：项目的第一行文字的基线对齐，这里要实现YGNodeSetBaselineFunc计算baseline位置
//stretch（默认值）：如果项目未设置高度或设为auto，将占满整个容器的高度。
bool proptyFunc_View_Align_Items(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setAlignItems(parseAlignItemsCssValue(propValue->getResult()->getString()));
    return true;
};

//子元素在交叉轴对齐方式，flex-wrap设置后生效
bool proptyFunc_View_Align_Content(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setAlignContent(parseAlignContentCssValue(propValue->getResult()->getString()));
    return true;
};

#pragma mark - Flex Item
//瓜分父布局剩余空间
//父：500
//子1: 100 grow：1
//子2: 150 grow：2
//子3: 100 grow：3
//剩余150
//A占比：1/(1+2+3)=1/6 A宽度：100+150*1/6=125
//B占比：2/(1+2+3)=1/3 B宽度：150+150*1/3=200
//C占比：3/(1+2+3)=1/2 C宽度：100+150*1/2=175
//如果A有子元素宽度占了50，那么A、B、C只能从500-50=450里面分
bool proptyFunc_View_Flex_Grow(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setFlexGrow(propValue->getResult()->getNumber());

    return true;
};


//子元素超过父元素大小，压缩子元素
//父：500
//子1: 300 shrink：1
//子2: 150 shrink：2
//子3: 200 shrink：3
//溢出150 压缩：300*1+150*2+200*3=1200
//A压缩率：300*1/1200=0.25 A宽度：300 - 150(溢出)*0.25 = 262.5
//B压缩率：150*2/1200=0.25 B宽度：150 - 150(溢出)*0.25 = 112.5
//C压缩率：200*3/1200=0.5  C宽度：200 - 150(溢出)*0.5 = 125
bool proptyFunc_View_Flex_Shrink(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setFlexShrink(propValue->getResult()->getNumber());
    return true;
};

//主轴的大小，如果row就是宽度，column就是高度
bool proptyFunc_View_Flex_Basis(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setFlexBasis(parseNumberStringToYGValue(propValue->getResult()->getString()));
    return true;
}

//单个item在交叉轴的对齐方式，align-items是父容器给所有子元素设置的在交叉轴对齐方式
bool proptyFunc_View_Align_Self(IQYBaseView *view, QYPropertyValue *propValue) {
    view->getNodeLayout()->setAlignSelf(parseAlignItemsCssValue(propValue->getResult()->getString()));
    return true;
}


//在这里新增属性方法
QYPropertySetter::QYPropertySetter() {
    mPropFuncMap.insert(std::pair("background-color", &proptyFunc_View_BackgroundColor));
    mPropFuncMap.insert(std::pair("width", &proptyFunc_View_Width));
    mPropFuncMap.insert(std::pair("height", &proptyFunc_View_Height));
    mPropFuncMap.insert(std::pair("top", &proptyFunc_View_Top));
    mPropFuncMap.insert(std::pair("left", &proptyFunc_View_Left));
    
    mPropFuncMap.insert(std::pair("display", &proptyFunc_View_Display));
    mPropFuncMap.insert(std::pair("flex-direction", &proptyFunc_View_Flex_Direction));
    mPropFuncMap.insert(std::pair("flex-wrap", &proptyFunc_View_Flex_Wrap));
    mPropFuncMap.insert(std::pair("justify-content", &proptyFunc_View_Justify_Content));
    mPropFuncMap.insert(std::pair("align-items", &proptyFunc_View_Align_Items));
    mPropFuncMap.insert(std::pair("align-content", &proptyFunc_View_Align_Content));

    mPropFuncMap.insert(std::pair("flex-grow", &proptyFunc_View_Flex_Grow));
    mPropFuncMap.insert(std::pair("flex-shrink", &proptyFunc_View_Flex_Shrink));
    mPropFuncMap.insert(std::pair("flex-basis", &proptyFunc_View_Flex_Basis));
    mPropFuncMap.insert(std::pair("align-self", &proptyFunc_View_Align_Self));

    

    
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

