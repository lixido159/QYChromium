
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
    void addChild(QYBaseDomNode * child);
    //对view赋值属性
    void performApplyWidgetViewTreeProperties();
    
    void performEnd();
    
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
public:
    void onDataUpdate(std::shared_ptr<QYPropertyValue> value) override;
protected:
    std::shared_ptr<QYPageCompContext> mPageCompContext;
    std::vector<QYBaseDomNode *> mChildNodeList;
    QYBaseDomNode *mParent = nullptr;
    std::shared_ptr<QYBaseNodeInfo> mNodeInfo = nullptr;
    std::shared_ptr<QYBaseWidget> mWidget;
    std::shared_ptr<QYPageInfo> mPageInfo;
    
};

#endif /* QYBaseDomNode_hpp */
