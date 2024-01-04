//
//  QYPropertyCssValueParser.cpp
//  QYView
//
//  Created by yinquan on 2024/1/4.
//

#include "QYPropertyCssValueParser.h"
#include <yoga/yoga.h>
int parseFlexDirectionCssValue(std::string value) {
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

int parseAlignItemsCssValue(std::string value) {
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
