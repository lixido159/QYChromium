//
//  QYPropertyCssValueParser.hpp
//  QYView
//
//  Created by yinquan on 2024/1/4.
//

#ifndef QYPropertyCssValueParser_hpp
#define QYPropertyCssValueParser_hpp

#include <stdio.h>
#include <string>
#include <yoga/yoga.h>

YGFlexDirection parseFlexDirectionCssValue(std::string value);
YGAlign parseAlignItemsCssValue(std::string value);
YGAlign parseAlignContentCssValue(std::string value);
YGWrap parseFlexWrapCssValue(std::string value);
YGJustify parseJustifyContentCssValue(std::string value);
YGValue parseNumberStringToYGValue(std::string value);
#endif /* QYPropertyCssValueParser_hpp */
