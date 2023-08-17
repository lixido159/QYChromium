
#ifndef QYBaseDomNode_hpp
#define QYBaseDomNode_hpp
#import "CommonHeader.h"
#import "QYBaseNodeInfo.h"

class QYBaseWidget;
///抽象的DomTree节点
class QYBaseDomNode {
public:
    QYBaseDomNode(QYBaseNodeInfo *info);
    std::vector<QYBaseDomNode *> mChildNodeList;
    QYBaseDomNode *mParent = nullptr;
    QYBaseNodeInfo *mNodeInfo = nullptr;
    QYBaseWidget *mWidget = nullptr;
    void addChild(QYBaseDomNode * child);
    //从上往下展开nodeTree，根据info->childNodeInfoList创建子QYBaseDomNode，添加到childNodeList
    //并且让其继续调用performExpandNodeTree，
    void performExpandNodeTree();
    //从上往下展开widgetTree
    void performExpandWidgetTree();
    //从上往下展开view
    void performExpandWidgetViewTree();
    //对view赋值属性
    void performApplyWidgetViewTreeProperties();
    
    void *getNativeView();
    
};

#endif /* QYBaseDomNode_hpp */
