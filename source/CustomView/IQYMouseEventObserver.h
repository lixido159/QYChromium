//
//  IQYMouseEventObserver.h
//  QYView
//
//  Created by 全寅 on 2023/11/17.
//

#ifndef IQYMouseEventObserver_h
#define IQYMouseEventObserver_h
class IQYMouseEventObserver {
public:
    virtual void onMouseUp() = 0;
    virtual void onMouseDown() = 0;
    virtual void onMouseMoved() = 0;

};

#endif /* IQYMouseEventObserver_h */
