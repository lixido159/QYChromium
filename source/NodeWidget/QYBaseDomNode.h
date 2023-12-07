
#ifndef QYBaseDomNode_hpp
#define QYBaseDomNode_hpp
#import "CommonHeader.h"
#import "QYBaseNodeInfo.h"
#include "IQYPropertyValueObserver.h"
#include "QYPageCompContext.h"
class QYBaseWidget;
///抽象的DomTree节点
class QYBaseDomNode : public IQYPropertyValueObserver, public std::enable_shared_from_this<QYBaseDomNode>  {
public:
    QYBaseDomNode(QYBaseNodeInfo *info);
    QYBaseDomNode(QYBaseNodeInfo *info, std::shared_ptr<QYPageCompContext> context);
    std::vector<QYBaseDomNode *> mChildNodeList;
    QYBaseDomNode *mParent = nullptr;
    QYBaseNodeInfo *mNodeInfo = nullptr;
    std::shared_ptr<QYBaseWidget> mWidget;
    void addChild(QYBaseDomNode * child);
    //对view赋值属性
    void performApplyWidgetViewTreeProperties();
    
    void *getNativeView();

    void setContext(std::shared_ptr<QYPageCompContext> context);
    
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
    std::shared_ptr<QYPageCompContext> mContext;
    
};

#endif /* QYBaseDomNode_hpp */
