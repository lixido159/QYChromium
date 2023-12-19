//
//  QYYogaLayout.cpp
//  QYView
//
//  Created by yinquan on 2023/12/19.
//

#include "QYYogaLayout.h"

#define YG_PROPERTY(type, lowercased_name, capitalized_name)      \
  type QYYogaLayout::get##capitalized_name() {                                        \
    return YGNodeStyleGet##capitalized_name(mNode);           \
  }                                                               \
                                                                  \
  void QYYogaLayout::set##capitalized_name(type lowercased_name) {          \
    YGNodeStyleSet##capitalized_name(mNode, lowercased_name); \
  }

#define YG_VALUE_PROPERTY(lowercased_name, capitalized_name)                \
  YGValue QYYogaLayout::get##capitalized_name() {                           \
    return YGNodeStyleGet##capitalized_name(mNode);                     \
  }                                                                         \
                                                                            \
  void QYYogaLayout::set##capitalized_name(YGValue lowercased_name) {                 \
    switch (lowercased_name.unit) {                                         \
      case YGUnitUndefined:                                                 \
        YGNodeStyleSet##capitalized_name(mNode, lowercased_name.value); \
        break;                                                              \
      case YGUnitPoint:                                                     \
        YGNodeStyleSet##capitalized_name(mNode, lowercased_name.value); \
        break;                                                              \
      case YGUnitPercent:                                                   \
        YGNodeStyleSet##capitalized_name##Percent(                          \
            mNode, lowercased_name.value);                              \
        break;                                                              \
      default:                                                              \
        assert(false);                                   \
    }                                                                       \
  }

#define YG_AUTO_VALUE_PROPERTY(lowercased_name, capitalized_name)           \
  YGValue QYYogaLayout::get##capitalized_name() {                                               \
    return YGNodeStyleGet##capitalized_name(mNode);                     \
  }                                                                         \
                                                                            \
  void QYYogaLayout::set##capitalized_name(YGValue lowercased_name) {                 \
    switch (lowercased_name.unit) {                                         \
      case YGUnitPoint:                                                     \
        YGNodeStyleSet##capitalized_name(mNode, lowercased_name.value); \
        break;                                                              \
      case YGUnitPercent:                                                   \
        YGNodeStyleSet##capitalized_name##Percent(                          \
            mNode, lowercased_name.value);                              \
        break;                                                              \
      case YGUnitAuto:                                                      \
        YGNodeStyleSet##capitalized_name##Auto(mNode);                  \
        break;                                                              \
      default:                                                              \
        assert(false);                                   \
    }                                                                       \
  }

#define YG_EDGE_PROPERTY_GETTER(                             \
    type, lowercased_name, capitalized_name, property, edge) \
  type QYYogaLayout::get##capitalized_name() {                                   \
    return YGNodeStyleGet##property(mNode, edge);        \
  }

#define YG_EDGE_PROPERTY_SETTER(                                \
    lowercased_name, capitalized_name, property, edge)          \
  void QYYogaLayout::set##capitalized_name(double lowercased_name) {     \
    YGNodeStyleSet##property(mNode, edge, lowercased_name); \
  }

#define YG_EDGE_PROPERTY(lowercased_name, capitalized_name, property, edge) \
  YG_EDGE_PROPERTY_GETTER(                                                  \
      double, lowercased_name, capitalized_name, property, edge)           \
  YG_EDGE_PROPERTY_SETTER(lowercased_name, capitalized_name, property, edge)

#define YG_VALUE_EDGE_PROPERTY_SETTER(                                       \
    objc_lowercased_name, objc_capitalized_name, c_name, edge)               \
  void QYYogaLayout::set##objc_capitalized_name(YGValue objc_lowercased_name) {        \
    switch (objc_lowercased_name.unit) {                                     \
      case YGUnitUndefined:                                                  \
        YGNodeStyleSet##c_name(mNode, edge, objc_lowercased_name.value); \
        break;                                                               \
      case YGUnitPoint:                                                      \
        YGNodeStyleSet##c_name(mNode, edge, objc_lowercased_name.value); \
        break;                                                               \
      case YGUnitPercent:                                                    \
        YGNodeStyleSet##c_name##Percent(                                     \
            mNode, edge, objc_lowercased_name.value);                    \
        break;                                                               \
      default:                                                               \
        assert(false);                                    \
    }                                                                        \
  }

#define YG_VALUE_EDGE_PROPERTY(                                   \
    lowercased_name, capitalized_name, property, edge)            \
  YG_EDGE_PROPERTY_GETTER(                                        \
      YGValue, lowercased_name, capitalized_name, property, edge) \
  YG_VALUE_EDGE_PROPERTY_SETTER(                                  \
      lowercased_name, capitalized_name, property, edge)

#define YG_VALUE_EDGES_PROPERTIES(lowercased_name, capitalized_name) \
  YG_VALUE_EDGE_PROPERTY(                                            \
      lowercased_name##Left,                                         \
      capitalized_name##Left,                                        \
      capitalized_name,                                              \
      YGEdgeLeft)                                                    \
  YG_VALUE_EDGE_PROPERTY(                                            \
      lowercased_name##Top,                                          \
      capitalized_name##Top,                                         \
      capitalized_name,                                              \
      YGEdgeTop)                                                     \
  YG_VALUE_EDGE_PROPERTY(                                            \
      lowercased_name##Right,                                        \
      capitalized_name##Right,                                       \
      capitalized_name,                                              \
      YGEdgeRight)                                                   \
  YG_VALUE_EDGE_PROPERTY(                                            \
      lowercased_name##Bottom,                                       \
      capitalized_name##Bottom,                                      \
      capitalized_name,                                              \
      YGEdgeBottom)                                                  \
  YG_VALUE_EDGE_PROPERTY(                                            \
      lowercased_name##Start,                                        \
      capitalized_name##Start,                                       \
      capitalized_name,                                              \
      YGEdgeStart)                                                   \
  YG_VALUE_EDGE_PROPERTY(                                            \
      lowercased_name##End,                                          \
      capitalized_name##End,                                         \
      capitalized_name,                                              \
      YGEdgeEnd)                                                     \
  YG_VALUE_EDGE_PROPERTY(                                            \
      lowercased_name##Horizontal,                                   \
      capitalized_name##Horizontal,                                  \
      capitalized_name,                                              \
      YGEdgeHorizontal)                                              \
  YG_VALUE_EDGE_PROPERTY(                                            \
      lowercased_name##Vertical,                                     \
      capitalized_name##Vertical,                                    \
      capitalized_name,                                              \
      YGEdgeVertical)                                                \
  YG_VALUE_EDGE_PROPERTY(                                            \
      lowercased_name, capitalized_name, capitalized_name, YGEdgeAll)



YGConfigRef getConfig() {
    static YGConfigRef globalConfig = nullptr;
    if (!globalConfig) {
        globalConfig = YGConfigNew();
    }
    return globalConfig;
}


QYYogaLayout::QYYogaLayout(QYBaseView *view): mView(view) {
    mNode = YGNodeNewWithConfig(getConfig());
}

QYYogaLayout::~QYYogaLayout() {
    YGNodeFree(mNode);
}


YGNodeRef QYYogaLayout::getNode() {
    return mNode;
}




YG_PROPERTY(YGDirection, direction, Direction);
YG_PROPERTY(YGFlexDirection, flexDirection, FlexDirection)
YG_PROPERTY(YGJustify, justifyContent, JustifyContent)
YG_PROPERTY(YGAlign, alignContent, AlignContent)
YG_PROPERTY(YGAlign, alignItems, AlignItems)
YG_PROPERTY(YGAlign, alignSelf, AlignSelf)
YG_PROPERTY(YGWrap, flexWrap, FlexWrap)
YG_PROPERTY(YGOverflow, overflow, Overflow)
YG_PROPERTY(YGDisplay, display, Display)
//
YG_PROPERTY(double, flex, Flex)
YG_PROPERTY(double, flexGrow, FlexGrow)
YG_PROPERTY(double, flexShrink, FlexShrink)
YG_AUTO_VALUE_PROPERTY(flexBasis, FlexBasis)
//
YG_VALUE_EDGE_PROPERTY(left, Left, Position, YGEdgeLeft)
YG_VALUE_EDGE_PROPERTY(top, Top, Position, YGEdgeTop)
YG_VALUE_EDGE_PROPERTY(right, Right, Position, YGEdgeRight)
YG_VALUE_EDGE_PROPERTY(bottom, Bottom, Position, YGEdgeBottom)
YG_VALUE_EDGE_PROPERTY(start, Start, Position, YGEdgeStart)
YG_VALUE_EDGE_PROPERTY(end, End, Position, YGEdgeEnd)
YG_VALUE_EDGES_PROPERTIES(margin, Margin)
YG_VALUE_EDGES_PROPERTIES(padding, Padding)
//
YG_EDGE_PROPERTY(borderLeftWidth, BorderLeftWidth, Border, YGEdgeLeft)
YG_EDGE_PROPERTY(borderTopWidth, BorderTopWidth, Border, YGEdgeTop)
YG_EDGE_PROPERTY(borderRightWidth, BorderRightWidth, Border, YGEdgeRight)
YG_EDGE_PROPERTY(borderBottomWidth, BorderBottomWidth, Border, YGEdgeBottom)
YG_EDGE_PROPERTY(borderStartWidth, BorderStartWidth, Border, YGEdgeStart)
YG_EDGE_PROPERTY(borderEndWidth, BorderEndWidth, Border, YGEdgeEnd)
YG_EDGE_PROPERTY(borderWidth, BorderWidth, Border, YGEdgeAll)
//
YG_AUTO_VALUE_PROPERTY(width, Width)
YG_AUTO_VALUE_PROPERTY(height, Height)
YG_VALUE_PROPERTY(minWidth, MinWidth)
YG_VALUE_PROPERTY(minHeight, MinHeight)
YG_VALUE_PROPERTY(maxWidth, MaxWidth)
YG_VALUE_PROPERTY(maxHeight, MaxHeight)
YG_PROPERTY(double, aspectRatio, AspectRatio)

YG_EDGE_PROPERTY(columnGap, ColumnGap, Gap, YGGutterColumn)
YG_EDGE_PROPERTY(rowGap, RowGap, Gap, YGGutterRow)
YG_EDGE_PROPERTY(gap, Gap, Gap, YGGutterAll)
