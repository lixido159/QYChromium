

#include "QYBaseDomNode.h"
#include "QYBaseWidget.h"
#include "QYFactory.h"

QYBaseDomNode::QYBaseDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info): mPageInfo(pageInfo), mNodeInfo(info){
    
}

QYBaseDomNode::QYBaseDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context):QYBaseDomNode(pageInfo, info) {
    mPageCompContext = context;
}

void QYBaseDomNode::addChild(std::shared_ptr<QYBaseDomNode> child) {
    this->mChildNodeList.push_back(child);
    child->mParent = weak_from_this();
}

void QYBaseDomNode::performExpandNodeTree() {
    std::vector<std::shared_ptr<IQYDomNodeCreatorItem>> items = createDomNodeCreatorItems(mNodeInfo->childNodeInfoList);
    
    for(std::shared_ptr<IQYDomNodeCreatorItem> item : items) {
        std::shared_ptr<QYBaseDomNode> node = item->createNode(mPageInfo, mPageCompContext);
        addChild(node);
        node->performExpandNodeTree();
    }
}

void QYBaseDomNode::performExpandWidgetTree() {
    mWidget = std::make_shared<QYBaseWidget>(mPageCompContext, mNodeInfo);
    auto parent = mParent.lock();
    if (parent) {
        parent->mWidget->addChildWidget(mWidget.get());
    }
    for(std::shared_ptr<QYBaseDomNode> node : mChildNodeList) {
        node->performExpandWidgetTree();
    }
}

void QYBaseDomNode::performExpandWidgetViewTree() {
    mWidget->performExpandViewTree();
}

void QYBaseDomNode::performApplyWidgetViewTreeProperties() {
    applyDefaultProperties();
    std::map<std::string, std::string>::iterator iter;
    for (iter = mNodeInfo->properties.begin(); iter != mNodeInfo->properties.end(); iter++) {
        std::shared_ptr<QYPropertyValue> proptyValue = std::make_shared<QYPropertyValue>(iter->first, iter->second, mPageCompContext);
        proptyValue->setObserver(this);
        mWidget->setProperty(proptyValue, true);
    }
    for(std::shared_ptr<QYBaseDomNode> node : mChildNodeList) {
        node->performApplyWidgetViewTreeProperties();
    }
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

#pragma mark - Private
void QYBaseDomNode::applyDefaultProperties() {
    std::map<std::string, std::string> defaultProperties = getDefaultProperties();
    for (std::map<std::string, std::string>::iterator iter = defaultProperties.begin(); iter != defaultProperties.end(); iter++) {
        std::shared_ptr<QYPropertyValue> proptyValue = std::make_shared<QYPropertyValue>(iter->first, iter->second, mPageCompContext);
        mWidget->setProperty(proptyValue, true);
    }
}

std::map<std::string, std::string> QYBaseDomNode::getDefaultProperties() {
    return {
    };
}



