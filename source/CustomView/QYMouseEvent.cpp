//
//  QYMouseEvent.cpp
//  QYView
//
//  Created by yinquan on 2023/11/16.
//

#include "QYMouseEvent.h"

QYMouseEvent::QYMouseEvent(QYMouseEventType mouseType, int locationX, int locationY) {
    type = mouseType;
    x = locationX;
    y = locationY;
}
