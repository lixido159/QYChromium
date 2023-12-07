

#include "QYBaseDomNode.h"
#include "QYBaseWidget.h"
#include "QYFactory.h"

QYBaseDomNode::QYBaseDomNode(QYBaseNodeInfo *info): mNodeInfo(info) {
    
}

QYBaseDomNode::QYBaseDomNode(QYBaseNodeInfo *info, std::shared_ptr<QYPageCompContext> context):QYBaseDomNode(info) {
    mContext = context;
}

void QYBaseDomNode::addChild(QYBaseDomNode * child) {
    this->mChildNodeList.push_back(child);
    child->mParent = this;
}

void QYBaseDomNode::performExpandNodeTree() {
    for(QYBaseNodeInfo *childInfo : mNodeInfo->childNodeInfoList) {
        QYBaseDomNode *node = createDomNodeWithNodeInfo(childInfo, mContext);
        addChild(node);
        node->performExpandNodeTree();
    }
}

void QYBaseDomNode::performExpandWidgetTree() {
    mWidget = std::make_shared<QYBaseWidget>(mContext, mNodeInfo->name);
    if (mParent) {
        mParent->mWidget->addChildWidget(mWidget.get());
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performExpandWidgetTree();
    }
}

void QYBaseDomNode::performExpandWidgetViewTree() {
    mWidget->performExpandViewTree();
}

void QYBaseDomNode::performApplyWidgetViewTreeProperties() {
    std::map<std::string, std::string>::iterator iter;
    for (iter = mNodeInfo->properties.begin(); iter != mNodeInfo->properties.end(); iter++) {
        std::shared_ptr<QYPropertyValue> proptyValue = std::make_shared<QYPropertyValue>(iter->first, iter->second, mContext);
        proptyValue->setObserver(this);
        mWidget->setProperty(proptyValue);
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performApplyWidgetViewTreeProperties();
    }
}


void *QYBaseDomNode::getNativeView() {
    return mWidget->getView()->getCustomView()->getNativeView();
}

void QYBaseDomNode::setContext(std::shared_ptr<QYPageCompContext> context) {
    mContext = context;
}

#pragma mark - IQYPropertyValueObserver
void QYBaseDomNode::onDataUpdate(std::shared_ptr<QYPropertyValue> value) {
    mWidget->setProperty(value);
}



