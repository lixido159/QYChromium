//
//  QYBaseCustomBaseView.hpp
//  libEVO
//
//  Created by yinquan on 2023/7/5.
//

#ifndef QYBaseCustomBaseView_hpp
#define QYBaseCustomBaseView_hpp

#include <stdio.h>
#include "IQYMouseEventObserver.h"
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
    virtual void setSize(float width, float height) = 0;
    virtual void setRect(float x, float y, float width, float height) = 0;
    virtual void setBackgroundColor(QY_Color color) = 0;
    virtual void addChildView(IQYBaseCustomBaseView *view) = 0;
    virtual void *getNativeView() = 0;
    virtual void setMouseEventObserver(IQYMouseEventObserver *observer) = 0;
    void *mNativeView;
};

#endif /* QYBaseCustomBaseView_hpp */
