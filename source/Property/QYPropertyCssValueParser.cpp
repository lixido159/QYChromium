//
//  QYPropertyCssValueParser.cpp
//  QYView
//
//  Created by yinquan on 2024/1/4.
//

#include "QYPropertyCssValueParser.h"
#include "QYYogaLayout.h"
YGFlexDirection parseFlexDirectionCssValue(std::string value) {
    if (value.compare("row") == 0) {
        return YGFlexDirectionRow;
    } else if (value.compare("row-reverse") == 0) {
        return YGFlexDirectionRowReverse;
    } else if (value.compare("column") == 0) {
        return YGFlexDirectionColumn;
    } else if (value.compare("column-reserve") == 0) {
        return YGFlexDirectionColumnReverse;
    }
    throw "invalid flex-direction";
}

YGAlign parseAlignItemsCssValue(std::string value) {
    if (value.compare("auto") == 0) {
        return YGAlignAuto;
    } else if (value.compare("flex-start") == 0) {
        return YGAlignFlexStart;
    } else if (value.compare("flex-end") == 0) {
        return YGAlignFlexEnd;
    } else if (value.compare("center") == 0) {
        return YGAlignCenter;
    } else if (value.compare("stretch") == 0) {
        return YGAlignStretch;
    } else if (value.compare("baseline") == 0) {
        return YGAlignBaseline;
    }
    throw "invalid align-items";
}

YGAlign parseAlignContentCssValue(std::string value) {
    if (value.compare("space-between") == 0) {
        return YGAlignSpaceBetween;
    } else if (value.compare("space-around") == 0) {
        return YGAlignSpaceAround;
    } else if (value.compare("space-evenly") == 0) {
        return YGAlignSpaceEvenly;
    }
    return parseAlignItemsCssValue(value);
}

YGWrap parseFlexWrapCssValue(std::string value) {
    if (value.compare("nowrap") == 0) {
        return YGWrapNoWrap;
    } else if (value.compare("wrap") == 0) {
        return YGWrapWrap;
    } else if (value.compare("wrap-reverse") == 0){
        return YGWrapWrapReverse;
    }
    throw "invalid flex-wrap";
}

YGJustify parseJustifyContentCssValue(std::string value) {
    if (value.compare("flex-start") == 0) {
        return YGJustifyFlexStart;
    } else if (value.compare("flex-end") == 0) {
        return YGJustifyFlexEnd;
    } else if (value.compare("center") == 0){
        return YGJustifyCenter;
    } else if (value.compare("space-between") == 0) {
        return YGJustifySpaceBetween;
    } else if (value.compare("space-around") == 0){
        return YGJustifySpaceAround;
    } else if (value.compare("space-evenly") == 0){
        return YGJustifySpaceEvenly;
    }
    throw "invalid justify-content";
}

YGValue parseNumberStringToYGValue(std::string value) {
    if (value.size() == 0) {
        return YGPointValue(0);;
    }
    size_t index = value.find("%");
    if (index == std::string::npos) {
        return YGPointValue(std::stof(value));
    } else if (value.length() > 1 && index == value.length() - 1){
        return YGPercentValue(std::stof(value.substr(0, index)));
    }
    throw "invalid percent value";
    
}
