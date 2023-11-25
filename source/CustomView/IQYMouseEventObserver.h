//
//  IQYMouseEventObserver.h
//  QYView
//
//  Created by 全寅 on 2023/11/17.
//

#ifndef IQYMouseEventObserver_h
#define IQYMouseEventObserver_h
#include "QYMouseEvent.h"
class IQYMouseEventObserver {
public:
    virtual void onMouseUp(const QYMouseEvent& mouseEvent) = 0;
    virtual void onMouseDown(const QYMouseEvent& mouseEvent) = 0;
    virtual void onMouseMoved(const QYMouseEvent& mouseEvent) = 0;

};

#endif /* IQYMouseEventObserver_h */
