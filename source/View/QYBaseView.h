#ifndef QYBaseView_hpp
#define QYBaseView_hpp
#include "IQYBaseView.h"
#include "IQYBaseCustomBaseView.h"
#include <vector>
///只是个View容器，真的View是mView，因为具体的view实现视平台而定
class QYBaseView : public IQYBaseView {
public:
    void addChildView(IQYBaseView *child) override;
    
    IQYBaseView *getParentView() override;
    void setParentView(IQYBaseView *parentView) override;
    
    IQYBaseCustomBaseView *getCustomView() override;
    void setCustomView(IQYBaseCustomBaseView *customView) override;

protected:
    IQYBaseView *mParentView = nullptr;
    std::vector<IQYBaseView *> mChildViews;
    IQYBaseCustomBaseView *mCustomView = nullptr;
};
#endif
