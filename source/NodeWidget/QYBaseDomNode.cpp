

#include "QYBaseDomNode.h"
#include "QYBaseWidget.h"
#include "QYFactory.h"

QYBaseDomNode::QYBaseDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info): mPageInfo(pageInfo), mNodeInfo(info){
    
}

QYBaseDomNode::QYBaseDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context):QYBaseDomNode(pageInfo, info) {
    mPageCompContext = context;
}

void QYBaseDomNode::addChild(QYBaseDomNode * child) {
    this->mChildNodeList.push_back(child);
    child->mParent = this;
}

void QYBaseDomNode::performExpandNodeTree() {
    for(std::shared_ptr<QYBaseNodeInfo> childInfo : mNodeInfo->childNodeInfoList) {
        QYBaseDomNode *node = createDomNode(mPageInfo, childInfo, mPageCompContext);
        addChild(node);
        node->performExpandNodeTree();
    }
}

void QYBaseDomNode::performExpandWidgetTree() {
    mWidget = std::make_shared<QYBaseWidget>(mPageCompContext, mNodeInfo->name);
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
        std::shared_ptr<QYPropertyValue> proptyValue = std::make_shared<QYPropertyValue>(iter->first, iter->second, mPageCompContext);
        proptyValue->setObserver(this);
        mWidget->setProperty(proptyValue, true);
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performApplyWidgetViewTreeProperties();
    }
}

void QYBaseDomNode::performEnd() {
    mWidget->getView()->requestLayout();
}

void *QYBaseDomNode::getNativeView() {
    return mWidget->getView()->getCustomView()->getNativeView();
}

void QYBaseDomNode::setContext(std::shared_ptr<QYPageCompContext> context) {
    mPageCompContext = context;
}

std::shared_ptr<QYBaseWidget> QYBaseDomNode::getWidget() {
    return mWidget;
}

#pragma mark - IQYPropertyValueObserver
void QYBaseDomNode::onDataUpdate(std::shared_ptr<QYPropertyValue> value) {
    mWidget->setProperty(value);
}



