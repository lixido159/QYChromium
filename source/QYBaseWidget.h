#ifndef QYBaseWidget_hpp
#define QYBaseWidget_hpp
#import "QYBaseView.h"
#import "QYBaseDomNode.h"
#import "QYPropertyValue.h"
///负责事件响应，持有view
class QYBaseWidget {
public:
    void addChildWidget(QYBaseWidget *child);
    void setProperty(std::shared_ptr<QYPropertyValue> value);
    QYPropertyValue *getProperty(std::string key);
    
    std::map<std::string, std::shared_ptr<QYPropertyValue> > getProptyValueMap();
    QYBaseWidget *getParentWidget();
    void setParentWidget(QYBaseWidget *parentWidget);
    
    void setView(IQYBaseView *view);
    IQYBaseView* getView();
private:
    std::map<std::string, std::shared_ptr<QYPropertyValue>> mProptyValueMap;
    QYBaseWidget *mParentWidget = nullptr;
    std::vector<QYBaseWidget *> mChildWidgets;
    IQYBaseView *mView = nullptr;
};
#endif
