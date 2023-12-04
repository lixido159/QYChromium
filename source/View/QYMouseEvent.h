//
//  QYMouseEvent.hpp
//  QYView
//
//  Created by yinquan on 2023/11/16.
//

#ifndef QYMouseEvent_hpp
#define QYMouseEvent_hpp

#include <stdio.h>
enum class QYMouseEventType {
    MOUSE_UNKNOWN = 0,
    MOUSE_LEFT_DOWN,
    MOUSE_LEFT_UP,
    MOUSE_RIGHT_DOWN,
    MOUSE_RIGHT_UP,
    MOUSE_MOVE
};

class QYMouseEvent {
public:
    QYMouseEvent(QYMouseEventType mouseType, double locationX, double locationY);
    double x;
    double y;
    QYMouseEventType type;
};

#endif /* QYMouseEvent_hpp */
