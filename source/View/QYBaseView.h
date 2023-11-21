#ifndef QYBaseView_hpp
#define QYBaseView_hpp
#include "IQYBaseView.h"
#include "IQYBaseCustomBaseView.h"
#include <vector>
///只是个View容器，真的View是mView，因为具体的view实现视平台而定
class QYBaseView : public IQYBaseView  {
public:
    void addChildView(IQYBaseView *child) override;
    
    IQYBaseView *getParentView() override;
    void setParentView(IQYBaseView *parentView) override;
    
    IQYBaseCustomBaseView *getCustomView() override;
    void setCustomView(IQYBaseCustomBaseView *customView) override;

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

protected:
    IQYBaseView *mParentView = nullptr;
    std::vector<IQYBaseView *> mChildViews;
    IQYBaseCustomBaseView *mCustomView = nullptr;
};
#endif
