

#include "QYBaseDomNode.h"
#include "QYBaseWidget.h"
#include "QYViewCreateFactory.h"


QYBaseDomNode::QYBaseDomNode(QYBaseNodeInfo *info): mNodeInfo(info) {
    
}
void QYBaseDomNode::addChild(QYBaseDomNode * child) {
    this->mChildNodeList.push_back(child);
    child->mParent = this;
}

void QYBaseDomNode::performExpandNodeTree() {
    for(QYBaseNodeInfo *childInfo : mNodeInfo->childNodeInfoList) {
        QYBaseDomNode *node = new QYBaseDomNode(childInfo);
        addChild(node);
        node->performExpandNodeTree();
    }
}

void QYBaseDomNode::performExpandWidgetTree() {
    mWidget = new QYBaseWidget;
    if (mParent) {
        mParent->mWidget->addChildWidget(mWidget);
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performExpandWidgetTree();
    }
}

void QYBaseDomNode::performExpandWidgetViewTree() {
    IQYBaseView *view = createViewWithNodeInfo(mNodeInfo);
    mWidget->setView(view);
    if (mWidget->getParentWidget()) {
        mWidget->getParentWidget()->getView()->addChildView(view);
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performExpandWidgetViewTree();
    }
}

void QYBaseDomNode::performApplyWidgetViewTreeProperties() {
    std::map<std::string, std::string>::iterator iter;
    for (iter = mNodeInfo->properties.begin(); iter != mNodeInfo->properties.end(); iter++) {
        QYPropertyValue *proptyValue = new QYPropertyValue(iter->first, iter->second);
        mWidget->setProperty(iter->first, proptyValue);
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performApplyWidgetViewTreeProperties();
    }
}


void *QYBaseDomNode::getNativeView() {
    return mWidget->getView()->getCustomView()->getNativeView();
}


