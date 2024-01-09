#ifndef QYBaseView_hpp
#define QYBaseView_hpp
#include "IQYBaseView.h"
#include "IQYBaseCustomBaseView.h"
#include <vector>
///只是个View容器，真的View是mView，因为具体的view实现视平台而定
class QYBaseView : public IQYBaseView  {
public:
    QYBaseView();
    void addChildView(IQYBaseView *child) override;
    std::vector<IQYBaseView *> getChildViews() override;
    
    IQYBaseView *getParentView() override;
    void setParentView(IQYBaseView *parentView) override;
    
    IQYBaseCustomBaseView *getCustomView() override;
    
public:
    virtual void setX(float x) override;
    virtual void setY(float y) override;
    virtual void setWidth(float width) override;
    virtual void setHeight(float height) override;
    virtual void setSize(QYSize size) override;
    virtual void setRect(QYRect rect) override;
    virtual void setBackgroundColor(QY_Color color) override;
    virtual QYYogaLayout *getNodeLayout() override;

    virtual float getX() override;
    virtual float getY() override;
    virtual float getWidth() override;
    virtual float getHeight() override;
    virtual QYSize getSize() override;
    virtual QYRect getRect() override;
    
    virtual void requestLayout() override;
    virtual void updateLayout() override;
protected:
    IQYBaseView *mParentView = nullptr;
    std::vector<IQYBaseView *> mChildViews;
    IQYBaseCustomBaseView *mCustomView = nullptr;
    std::shared_ptr<QYYogaLayout> mNodeLayout;
};
#endif
