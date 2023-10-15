//
//  QYBaseCustomView.hpp
//  libEVO
//
//  Created by yinquan on 2023/7/5.
//

#ifndef QYBaseCustomView_hpp
#define QYBaseCustomView_hpp

#include <stdio.h>
#include "IQYBaseCustomBaseView.h"

class QYBaseCustomView : public IQYBaseCustomBaseView{
public:
    virtual void setX(float x) override;
    virtual void setY(float y) override;
    virtual void setWidth(float width) override;
    virtual void setHeight(float height) override;
    virtual void setSize(float width, float height) override;
    virtual void setRect(float x, float y, float width, float height) override;
    virtual void setBackgroundColor(QY_Color color) override;
    virtual void addChildView(IQYBaseCustomBaseView *view) override;
    virtual void *getNativeView() override;
    QYBaseCustomView();
};

#endif /* QYBaseCustomView_hpp */
