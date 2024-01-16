

#include "QYBaseDomNode.h"
#include "QYBaseWidget.h"
#include "QYFactory.h"

QYBaseDomNode::QYBaseDomNode(std::shared_ptr<QYBaseDomNode> parent, std::shared_ptr<QYBaseNodeInfo> info): mParent(parent), mNodeInfo(info){
    if (parent) {
        mPageInfo = parent->getPageInfo();
    }
}

QYBaseDomNode::QYBaseDomNode(std::shared_ptr<QYBaseDomNode> parent, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context): QYBaseDomNode(parent, info) {
    if (parent) {
        mPageInfo = parent->getPageInfo();
    }
    mPageCompContext = context;
}

void QYBaseDomNode::addChild(std::shared_ptr<QYBaseDomNode> child) {
    this->mChildNodeList.push_back(child);
    child->mParent = shared_from_this();
}

void QYBaseDomNode::performExpandNodeTree() {
    auto parent = mParent.lock();
    if (parent) {
        parent->addChild(shared_from_this());
    }
    std::vector<std::shared_ptr<IQYDomNodeCreatorItem>> items = createDomNodeCreatorItems(mNodeInfo->childNodeInfoList);
    
    for(std::shared_ptr<IQYDomNodeCreatorItem> item : items) {
        std::shared_ptr<QYBaseDomNode> node = item->createNode(shared_from_this(), mPageCompContext);
        node->performExpandNodeTree();
    }
}

void QYBaseDomNode::performExpandWidgetTree() {
    mWidget = std::make_shared<QYBaseWidget>(mPageCompContext, getNodeType());
    auto parent = mParent.lock();
    if (parent) {
        parent->getWidget()->addChildWidget(mWidget);
    }
    for(std::shared_ptr<QYBaseDomNode> node : mChildNodeList) {
        node->performExpandWidgetTree();
    }
}

void QYBaseDomNode::performAttachParentView(std::shared_ptr<IQYBaseView> parentView) {
    if (parentView) {
        parentView->addChildView(mWidget->getView());
    }
    for(std::shared_ptr<QYBaseDomNode> node : mChildNodeList) {
        node->performAttachParentView(mWidget->getView());
    }
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

std::string QYBaseDomNode::getNodeType() {
    if (mNodeInfo) {
        return mNodeInfo->name;
    } else {
        return "";
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

void QYBaseDomNode::setPageInfo(std::shared_ptr<QYPageInfo> pageInfo) {
    mPageInfo = pageInfo;
}

std::shared_ptr<QYPageInfo> QYBaseDomNode::getPageInfo() {
    return mPageInfo;
}

std::shared_ptr<IQYBaseView> QYBaseDomNode::getParentView() {
    auto parent = mParent.lock();
    if (parent) {
        return parent->getView();
    }
    return nullptr;
}


std::shared_ptr<IQYBaseView> QYBaseDomNode::getView() {
    return mWidget->getView();
}

void QYBaseDomNode::removeChildNode(std::shared_ptr<QYBaseDomNode> childNode) {
    mWidget->removeChildWidget(childNode->getWidget());
    mChildNodeList.erase(std::remove(mChildNodeList.begin(), mChildNodeList.end(), childNode), mChildNodeList.end());
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



