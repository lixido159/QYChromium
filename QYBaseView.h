#ifndef QYBaseView_hpp
#define QYBaseView_hpp
#import "ui/views/view.h"
///只是个View容器，真的View是mView，因为具体的view实现视平台而定
class QYBaseView {

public:
    QYBaseView *mParent = nullptr;
    std::vector<QYBaseView *> mChildViews;
    views::View *mView = nullptr;
    void addChild(QYBaseView *child);
};
#endif
