
#ifndef QYBaseDomNode_hpp
#define QYBaseDomNode_hpp
#import "CommonHeader.h"
#include <QYFileInfo/QYBaseNodeInfo.h>
#include "IQYPropertyValueObserver.h"
#include "QYPageCompContext.h"

#include <QYFileInfo/QYPageInfo.h>

class QYBaseWidget;
///抽象的DomTree节点
class QYBaseDomNode : public IQYPropertyValueObserver, public std::enable_shared_from_this<QYBaseDomNode>  {
public:
    QYBaseDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info);
    QYBaseDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context);
    void addChild(std::shared_ptr<QYBaseDomNode> child);
        
    void *getNativeView();

    void setContext(std::shared_ptr<QYPageCompContext> context);
    
    std::shared_ptr<QYBaseWidget> getWidget();
public:
    //从上往下展开nodeTree，根据info->childNodeInfoList创建子QYBaseDomNode，添加到childNodeList
    //并且让其继续调用performExpandNodeTree，
    virtual void performExpandNodeTree();
    //从上往下展开widgetTree
    virtual void performExpandWidgetTree();
    //从上往下展开view
    virtual void performExpandWidgetViewTree();
    //对view赋值属性
    virtual void performApplyWidgetViewTreeProperties();

public:
    virtual void onDataUpdate(std::shared_ptr<QYPropertyValue> value) override;
private:
    void applyDefaultProperties();
    std::map<std::string, std::string> getDefaultProperties();
protected:
    std::shared_ptr<QYPageCompContext> mPageCompContext;
    std::vector<std::shared_ptr<QYBaseDomNode>> mChildNodeList;
    std::weak_ptr<QYBaseDomNode> mParent;
    std::shared_ptr<QYBaseNodeInfo> mNodeInfo;
    std::shared_ptr<QYBaseWidget> mWidget;
    std::shared_ptr<QYPageInfo> mPageInfo;
    
};

#endif /* QYBaseDomNode_hpp */
