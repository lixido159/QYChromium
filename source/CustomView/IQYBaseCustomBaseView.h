//
//  QYBaseCustomBaseView.hpp
//  libEVO
//
//  Created by yinquan on 2023/7/5.
//

#ifndef QYBaseCustomBaseView_hpp
#define QYBaseCustomBaseView_hpp

#include <stdio.h>
#include <memory>
#include "IQYMouseEventObserver.h"
#include "QYDefine.h"

struct QY_Color {
    int r;
    int g;
    int b;
    int a;
};

class IQYBaseCustomBaseView {
public:
    virtual void setX(float x) = 0;
    virtual void setY(float y) = 0;
    virtual void setWidth(float width) = 0;
    virtual void setHeight(float height) = 0;
    virtual void setSize(QYSize size) = 0;
    virtual void setRect(QYRect rect) = 0;
    virtual void setBackgroundColor(QY_Color color) = 0;
    
    virtual float getX() = 0;
    virtual float getY() = 0;
    virtual float getWidth() = 0;
    virtual float getHeight() = 0;
    virtual QYSize getSize() = 0;
    virtual QYRect getRect() = 0;

    
    virtual void addChildView(std::shared_ptr<IQYBaseCustomBaseView> view) = 0;
    virtual void *getNativeView() = 0;
    virtual void setMouseEventObserver(IQYMouseEventObserver *observer) = 0;
    void *mNativeView;
};

#endif /* QYBaseCustomBaseView_hpp */
