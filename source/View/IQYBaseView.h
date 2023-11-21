//
//  IQYBaseView.h
//  QYView
//
//  Created by yinquan on 2023/10/15.
//

#ifndef IQYBaseView_h
#define IQYBaseView_h

#include "IQYBaseCustomBaseView.h"
#include <vector>

class IQYBaseView {
public:
    virtual void setX(float x) = 0;
    virtual void setY(float y) = 0;
    virtual void setWidth(float width) = 0;
    virtual void setHeight(float height) = 0;
    virtual void setSize(float width, float height) = 0;
    virtual void setRect(float x, float y, float width, float height) = 0;
    virtual void setBackgroundColor(QY_Color color) = 0;

    virtual void addChildView(IQYBaseView *child) = 0;
    virtual IQYBaseView *getParentView() = 0;
    virtual void setParentView(IQYBaseView *parentView) = 0;
    
    virtual IQYBaseCustomBaseView *getCustomView() = 0;
};

#endif /* IQYBaseView_h */
