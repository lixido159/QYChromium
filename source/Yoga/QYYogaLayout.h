//
//  QYYogaLayout.hpp
//  QYView
//
//  Created by yinquan on 2023/12/19.
//

#ifndef QYYogaLayout_hpp
#define QYYogaLayout_hpp

#define YG_PROPERTY_DEFINE(type, lowercased_name, capitalized_name)      \
  type get##capitalized_name();\
  void set##capitalized_name(type lowercased_name);

#define YG_VALUE_PROPERTY_DEFINE(lowercased_name, capitalized_name)                \
    YGValue get##capitalized_name();                                           \
    void set##capitalized_name(YGValue lowercased_name);


#define YG_AUTO_VALUE_PROPERTY_DEFINE(lowercased_name, capitalized_name)           \
    YGValue get##capitalized_name();\
    void set##capitalized_name(YGValue lowercased_name);

#define YG_VALUE_EDGE_PROPERTY_SETTER_DEFINE(                                       \
    objc_lowercased_name, objc_capitalized_name, c_name, edge)               \
    void set##objc_capitalized_name(YGValue objc_lowercased_name);

#define YG_EDGE_PROPERTY_GETTER_DEFINE(                             \
    type, lowercased_name, capitalized_name, property, edge) \
    type get##capitalized_name();

#define YG_VALUE_EDGE_PROPERTY_DEFINE(                                   \
    lowercased_name, capitalized_name, property, edge)            \
  YG_EDGE_PROPERTY_GETTER_DEFINE(                                        \
      YGValue, lowercased_name, capitalized_name, property, edge) \
  YG_VALUE_EDGE_PROPERTY_SETTER_DEFINE(                                  \
      lowercased_name, capitalized_name, property, edge)


#define YG_EDGE_PROPERTY_SETTER_DEFINE(                                \
    lowercased_name, capitalized_name, property, edge)          \
    void set##capitalized_name(double lowercased_name);

#define YG_EDGE_PROPERTY_DEFINE(lowercased_name, capitalized_name, property, edge) \
  YG_EDGE_PROPERTY_GETTER_DEFINE(                                                  \
      double, lowercased_name, capitalized_name, property, edge)           \
  YG_EDGE_PROPERTY_SETTER_DEFINE(lowercased_name, capitalized_name, property, edge)


#define YG_VALUE_EDGES_PROPERTIES_DEFINE(lowercased_name, capitalized_name) \
  YG_VALUE_EDGE_PROPERTY_DEFINE(                                            \
      lowercased_name##Left,                                         \
      capitalized_name##Left,                                        \
      capitalized_name,                                              \
      YGEdgeLeft)                                                    \
  YG_VALUE_EDGE_PROPERTY_DEFINE(                                            \
      lowercased_name##Top,                                          \
      capitalized_name##Top,                                         \
      capitalized_name,                                              \
      YGEdgeTop)                                                     \
  YG_VALUE_EDGE_PROPERTY_DEFINE(                                            \
      lowercased_name##Right,                                        \
      capitalized_name##Right,                                       \
      capitalized_name,                                              \
      YGEdgeRight)                                                   \
  YG_VALUE_EDGE_PROPERTY_DEFINE(                                            \
      lowercased_name##Bottom,                                       \
      capitalized_name##Bottom,                                      \
      capitalized_name,                                              \
      YGEdgeBottom)                                                  \
  YG_VALUE_EDGE_PROPERTY_DEFINE(                                            \
      lowercased_name##Start,                                        \
      capitalized_name##Start,                                       \
      capitalized_name,                                              \
      YGEdgeStart)                                                   \
  YG_VALUE_EDGE_PROPERTY_DEFINE(                                            \
      lowercased_name##End,                                          \
      capitalized_name##End,                                         \
      capitalized_name,                                              \
      YGEdgeEnd)                                                     \
  YG_VALUE_EDGE_PROPERTY_DEFINE(                                            \
      lowercased_name##Horizontal,                                   \
      capitalized_name##Horizontal,                                  \
      capitalized_name,                                              \
      YGEdgeHorizontal)                                              \
  YG_VALUE_EDGE_PROPERTY_DEFINE(                                            \
      lowercased_name##Vertical,                                     \
      capitalized_name##Vertical,                                    \
      capitalized_name,                                              \
      YGEdgeVertical)                                                \
  YG_VALUE_EDGE_PROPERTY_DEFINE(                                            \
      lowercased_name, capitalized_name, capitalized_name, YGEdgeAll)


#include <stdio.h>
#include <yoga/Yoga.h>

class QYBaseView;
class QYYogaLayout {
public:
    QYYogaLayout(QYBaseView *view);
    ~QYYogaLayout();
    YGNodeRef getNode();
    YG_PROPERTY_DEFINE(YGDirection, direction, Direction);
    YG_PROPERTY_DEFINE(YGFlexDirection, flexDirection, FlexDirection)
    YG_PROPERTY_DEFINE(YGJustify, justifyContent, JustifyContent)
    YG_PROPERTY_DEFINE(YGAlign, alignContent, AlignContent)
    YG_PROPERTY_DEFINE(YGAlign, alignItems, AlignItems)
    YG_PROPERTY_DEFINE(YGAlign, alignSelf, AlignSelf)
    YG_PROPERTY_DEFINE(YGWrap, flexWrap, FlexWrap)
    YG_PROPERTY_DEFINE(YGOverflow, overflow, Overflow)
    YG_PROPERTY_DEFINE(YGDisplay, display, Display)
    YG_PROPERTY_DEFINE(double, flex, Flex)
    YG_PROPERTY_DEFINE(double, flexGrow, FlexGrow)
    YG_PROPERTY_DEFINE(double, flexShrink, FlexShrink)

    YG_AUTO_VALUE_PROPERTY_DEFINE(flexBasis, FlexBasis)
    
    YG_VALUE_EDGE_PROPERTY_DEFINE(left, Left, Position, YGEdgeLeft)
    YG_VALUE_EDGE_PROPERTY_DEFINE(top, Top, Position, YGEdgeTop)
    YG_VALUE_EDGE_PROPERTY_DEFINE(right, Right, Position, YGEdgeRight)
    YG_VALUE_EDGE_PROPERTY_DEFINE(bottom, Bottom, Position, YGEdgeBottom)
    YG_VALUE_EDGE_PROPERTY_DEFINE(start, Start, Position, YGEdgeStart)
    YG_VALUE_EDGE_PROPERTY_DEFINE(end, End, Position, YGEdgeEnd)
    
    YG_VALUE_EDGES_PROPERTIES_DEFINE(margin, Margin)
    YG_VALUE_EDGES_PROPERTIES_DEFINE(padding, Padding)
    
    YG_EDGE_PROPERTY_DEFINE(borderLeftWidth, BorderLeftWidth, Border, YGEdgeLeft)
    YG_EDGE_PROPERTY_DEFINE(borderTopWidth, BorderTopWidth, Border, YGEdgeTop)
    YG_EDGE_PROPERTY_DEFINE(borderRightWidth, BorderRightWidth, Border, YGEdgeRight)
    YG_EDGE_PROPERTY_DEFINE(borderBottomWidth, BorderBottomWidth, Border, YGEdgeBottom)
    YG_EDGE_PROPERTY_DEFINE(borderStartWidth, BorderStartWidth, Border, YGEdgeStart)
    YG_EDGE_PROPERTY_DEFINE(borderEndWidth, BorderEndWidth, Border, YGEdgeEnd)
    YG_EDGE_PROPERTY_DEFINE(borderWidth, BorderWidth, Border, YGEdgeAll)

    YG_AUTO_VALUE_PROPERTY_DEFINE(width, Width)
    YG_AUTO_VALUE_PROPERTY_DEFINE(height, Height)

    YG_VALUE_PROPERTY_DEFINE(minWidth, MinWidth)
    YG_VALUE_PROPERTY_DEFINE(minHeight, MinHeight)
    YG_VALUE_PROPERTY_DEFINE(maxWidth, MaxWidth)
    YG_VALUE_PROPERTY_DEFINE(maxHeight, MaxHeight)

    YG_PROPERTY_DEFINE(double, aspectRatio, AspectRatio)

    YG_EDGE_PROPERTY_DEFINE(columnGap, ColumnGap, Gap, YGGutterColumn)
    YG_EDGE_PROPERTY_DEFINE(rowGap, RowGap, Gap, YGGutterRow)
    YG_EDGE_PROPERTY_DEFINE(gap, Gap, Gap, YGGutterAll)

private:
    YGNodeRef mNode;
    QYBaseView *mView;
};

#endif /* QYYogaLayout_hpp */
