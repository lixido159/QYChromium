//
//  QYIfDomNode.cpp
//  QYView
//
//  Created by yinquan on 2024/1/10.
//

#include "QYIfDomNode.h"
#include "QYBaseWidget.h"
#include "QYFactory.h"
bool isIfProperty(std::map<std::string, std::string>::iterator iter) {
    if (iter->first.compare("qy:if") == 0) {
        return true;
    } else if (iter->first.compare("qy:elif") == 0) {
        return true;
    } else if (iter->first.compare("qy:else") == 0) {
        return true;
    }
    return false;
}

QYIfDomNode::QYIfDomNode(std::shared_ptr<QYBaseDomNode> parent,
                         std::vector<std::shared_ptr<QYBaseNodeInfo>> infoList, std::shared_ptr<QYPageCompContext> context): QYBaseDomNode(parent, nullptr, context), mInfoList(infoList) {
    init();
}

void QYIfDomNode::performExpandNodeTree() {
    auto parent = mParent.lock();
    if (parent) {
        parent->addChild(shared_from_this());
    }

    std::vector<std::shared_ptr<IQYDomNodeCreatorItem>> items = createDomNodeCreatorItems(mInfoList);
    
    for(std::shared_ptr<QYBaseNodeInfo> info : mInfoList) {
        std::shared_ptr<QYBaseDomNode> domNode = std::make_shared<QYBaseDomNode>(shared_from_this(), info, mPageCompContext);
        domNode->performExpandNodeTree();
    }

}

void QYIfDomNode::performExpandWidgetTree() {
    QYBaseDomNode::performExpandWidgetTree();
}

void QYIfDomNode::performAttachParentView(std::shared_ptr<IQYBaseView> parentView) {
    
}

void QYIfDomNode::performApplyWidgetViewTreeProperties() {
    
}



void QYIfDomNode::onDataUpdate(std::shared_ptr<QYPropertyValue> value) {
    int validIndex = calculateValidNodeIndex();
    if (validIndex == mValidIndex || validIndex == -1) {
        return;
    } else {
        std::shared_ptr<QYBaseDomNode> validDomNode = mChildNodeList[mValidIndex];
    }
    removeDomNode();
    mValidIndex = validIndex;
    renderNode();
}


#pragma mark - Private
void QYIfDomNode::renderNode() {
    std::shared_ptr<QYBaseDomNode> validDomNode = mChildNodeList[mValidIndex];
    validDomNode->performAttachParentView(getParentView());
    validDomNode->performApplyWidgetViewTreeProperties();
}

void QYIfDomNode::removeDomNode() {
    std::shared_ptr<QYBaseDomNode> validDomNode = mChildNodeList[mValidIndex];
    removeChildNode(validDomNode);
}

void QYIfDomNode::addDomNode() {
    
}


int QYIfDomNode::calculateValidNodeIndex() {
    for (int i=0; i<mIfPropertyList.size(); i++) {
        std::shared_ptr<QYPropertyValue> proptyValue = mIfPropertyList[i];
        if (proptyValue->getKey().compare("qy:else") == 0) {
            return i;
        }
        if (proptyValue->getBoolValue()) {
            return i;
        }
    }
    return -1;
}

void QYIfDomNode::init() {
    std::vector<std::shared_ptr<QYBaseNodeInfo>>::iterator infoIter;
    for (infoIter = mInfoList.begin(); infoIter != mInfoList.end(); infoIter++) {
        std::map<std::string, std::string>::iterator kvIter;
        for (kvIter = (*infoIter)->properties.begin(); kvIter != (*infoIter)->properties.end(); kvIter++) {
            if (isIfProperty(kvIter)) {
                std::shared_ptr<QYPropertyValue> proptyValue = std::make_shared<QYPropertyValue>(kvIter->first, kvIter->second, mPageCompContext);
                proptyValue->setObserver(this);
                mIfPropertyList.push_back(proptyValue);
            }
        }
    }
    mValidIndex = calculateValidNodeIndex();
}

