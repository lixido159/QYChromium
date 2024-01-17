#ifndef QYBaseWidget_hpp
#define QYBaseWidget_hpp
#import "QYBaseView.h"
#import "QYBaseDomNode.h"
#import "QYPropertyValue.h"

///负责事件响应，持有view
class QYBaseWidget : public IQYMouseEventObserver, public std::enable_shared_from_this<QYBaseWidget> {
public:
    QYBaseWidget(std::shared_ptr<QYPageCompContext> context, std::string type);
    void addChildWidget(std::shared_ptr<QYBaseWidget> child);
    void removeFromParentWidget();
    void setProperty(std::shared_ptr<QYPropertyValue> value, bool noLayout = false);
    QYPropertyValue *getProperty(std::string key);
    
    std::vector<std::shared_ptr<QYBaseWidget>>& getChildWidgets();
    
    std::map<std::string, std::shared_ptr<QYPropertyValue> > getProptyValueMap();
    std::shared_ptr<QYBaseWidget> getParentWidget();
    void setParentWidget(std::shared_ptr<QYBaseWidget> parentWidget);
    void setView(std::shared_ptr<IQYBaseView> view);
    std::shared_ptr<IQYBaseView> getView();
    std::shared_ptr<QYBaseWidget> getChildWidgetById(std::string childId);
    std::shared_ptr<QYPageCompContext> getPageCompContext();
    QYJSValue *getElementValue();
    void registerElementInterface();
    void requestLayout();
    void onSizeChange();
    //IQYMouseEventObserver
    virtual void onMouseUp(const QYMouseEvent& mouseEvent) override;
    virtual void onMouseDown(const QYMouseEvent& mouseEvent) override;
    virtual void onMouseMoved(const QYMouseEvent& mouseEvent) override;

private:
    std::map<std::string, std::shared_ptr<QYPropertyValue>> mProptyValueMap;
    std::weak_ptr<QYBaseWidget> mParentWidget ;
    std::vector<std::shared_ptr<QYBaseWidget>> mChildWidgets;
    std::shared_ptr<IQYBaseView> mView ;
    std::shared_ptr<QYPageCompContext> mPageCompContext;
    std::string mType;
    void callMouseEvent(std::string event, const QYMouseEvent& mouseEvent);
    std::unique_ptr<QYJSValue> mElementValue;
};
#endif
