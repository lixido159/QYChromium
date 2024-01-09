//
//  IQYBaseView.h
//  QYView
//
//  Created by yinquan on 2023/10/15.
//

#ifndef IQYBaseView_h
#define IQYBaseView_h

#include "IQYBaseCustomBaseView.h"
#include <yoga/yoga.h>
#include <vector>
#include "QYYogaLayout.h"
class IQYBaseView {
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
    
    virtual void addChildView(IQYBaseView *child) = 0;
    virtual std::vector<IQYBaseView *> getChildViews() = 0;
    virtual IQYBaseView *getParentView() = 0;
    virtual void setParentView(IQYBaseView *parentView) = 0;
    
    virtual IQYBaseCustomBaseView *getCustomView() = 0;
    
    virtual QYYogaLayout *getNodeLayout() = 0;

    virtual void requestLayout() = 0;
    
    virtual void updateLayout() = 0;
};

#endif /* IQYBaseView_h */
