#ifndef QYBaseView_hpp
#define QYBaseView_hpp
#include "IQYBaseView.h"
#include "IQYBaseCustomBaseView.h"
#include <vector>
///只是个View容器，真的View是mView，因为具体的view实现视平台而定
class QYBaseView : public IQYBaseView, public std::enable_shared_from_this<QYBaseView>{
public:
    QYBaseView();
    void addChildView(std::shared_ptr<IQYBaseView> child) override;
    std::vector<std::shared_ptr<IQYBaseView>> getChildViews() override;
    
    std::shared_ptr<IQYBaseView> getParentView() override;
    void setParentView(std::shared_ptr<IQYBaseView> parentView) override;
    
    std::shared_ptr<IQYBaseCustomBaseView> getCustomView() override;
    
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
    std::weak_ptr<IQYBaseView> mParentView;
    std::vector<std::shared_ptr<IQYBaseView>> mChildViews;
    std::shared_ptr<IQYBaseCustomBaseView> mCustomView ;
    std::shared_ptr<QYYogaLayout> mNodeLayout;
};
#endif
