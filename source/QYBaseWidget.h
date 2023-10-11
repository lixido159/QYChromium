#ifndef QYBaseWidget_hpp
#define QYBaseWidget_hpp
#import "QYBaseView.h"
#import "QYBaseDomNode.h"
#import "QYPropertyValue.h"
///负责事件响应，持有view
class QYBaseWidget {
public:
    QYBaseWidget *mParent = nullptr;
    std::vector<QYBaseWidget *> mChildWidgets;
    QYBaseView *mView = nullptr;
    void addChild(QYBaseWidget *child);
    void setProperty(std::string key, QYPropertyValue *value);
    QYPropertyValue *getProperty(std::string key);
private:
    std::map<std::string, QYPropertyValue *> mPropertyValueMap;
};
#endif
