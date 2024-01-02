#ifndef QYBaseWidget_hpp
#define QYBaseWidget_hpp
#import "QYBaseView.h"
#import "QYBaseDomNode.h"
#import "QYPropertyValue.h"

///负责事件响应，持有view
class QYBaseWidget : public IQYMouseEventObserver {
public:
    QYBaseWidget(std::shared_ptr<QYPageCompContext> context, std::string type);
    void addChildWidget(QYBaseWidget *child);
    void setProperty(std::shared_ptr<QYPropertyValue> value, bool noLayout = false);
    QYPropertyValue *getProperty(std::string key);
    
    std::map<std::string, std::shared_ptr<QYPropertyValue> > getProptyValueMap();
    QYBaseWidget *getParentWidget();
    void setParentWidget(QYBaseWidget *parentWidget);
    void setView(IQYBaseView *view);
    IQYBaseView* getView();
    QYBaseWidget *getChildWidgetById(std::string childId);
    std::shared_ptr<QYPageCompContext> getPageCompContext();
    QYJSValue *getElementValue();
    void performExpandViewTree();
    void registerElementInterface();
    //IQYMouseEventObserver
    virtual void onMouseUp(const QYMouseEvent& mouseEvent) override;
    virtual void onMouseDown(const QYMouseEvent& mouseEvent) override;
    virtual void onMouseMoved(const QYMouseEvent& mouseEvent) override;

private:
    std::map<std::string, std::shared_ptr<QYPropertyValue>> mProptyValueMap;
    QYBaseWidget *mParentWidget = nullptr;
    std::vector<QYBaseWidget *> mChildWidgets;
    IQYBaseView *mView = nullptr;
    std::shared_ptr<QYPageCompContext> mPageCompContext;
    std::string mType = "";
    void callMouseEvent(std::string event, const QYMouseEvent& mouseEvent);
    std::unique_ptr<QYJSValue> mElementValue;
};
#endif
