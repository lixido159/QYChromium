#ifndef QYBaseWidget_hpp
#define QYBaseWidget_hpp
#import "QYBaseView.h"
#import "QYBaseDomNode.h"
///负责事件响应，持有view
class QYBaseWidget {
public:
    QYBaseWidget *mParent = nullptr;
    std::vector<QYBaseWidget *> mChildWidgets;
    QYBaseView *mView = nullptr;
    void addChild(QYBaseWidget *child);
};
#endif
