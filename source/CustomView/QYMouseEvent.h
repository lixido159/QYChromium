//
//  QYMouseEvent.hpp
//  QYView
//
//  Created by 全寅 on 2023/11/16.
//

#ifndef QYMouseEvent_hpp
#define QYMouseEvent_hpp

#include <stdio.h>
enum class QYMouseEventType {
    MOUSE_UNKNOWN = 0,
    MOUSE_UP,
    MOUSE_DOWN,
    MOUSE_MOVE
};

class QYMouseEvent {
public:
    QYMouseEvent(QYMouseEventType mouseType, int locationX, int locationY);
    int x;
    int y;
    QYMouseEventType type;
};

#endif /* QYMouseEvent_hpp */
