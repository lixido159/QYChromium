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
    if (mValidIndex != -1) {
        std::shared_ptr<QYBaseDomNode> childDomNode = std::make_shared<QYBaseDomNode>(shared_from_this(), mInfoList[mValidIndex], mPageCompContext);
        mCacheDomNodeMap[mValidIndex] = childDomNode;
        childDomNode->performExpandNodeTree();
    }}

void QYIfDomNode::performExpandWidgetTree() {
    mWidget = std::make_shared<QYBaseWidget>(mPageCompContext, getNodeType());
    auto parent = mParent.lock();
    if (parent) {
        parent->getWidget()->addChildWidget(mWidget);
    }
    if (mChildNodeList[0]) {
        mChildNodeList[0]->performExpandWidgetTree();
    }
    
}

void QYIfDomNode::performAttachParentView(std::shared_ptr<IQYBaseView> parentView) {
    mRealParentView = parentView;
    if (mChildNodeList[0]) {
        mChildNodeList[0]->performAttachParentView(parentView);
    }
}

void QYIfDomNode::performApplyWidgetViewTreeProperties() {
    if (mChildNodeList[0]) {
        mChildNodeList[0]->performApplyWidgetViewTreeProperties();
    }
}



void QYIfDomNode::onDataUpdate(std::shared_ptr<QYPropertyValue> value) {
    int validIndex = calculateValidNodeIndex();
    if (validIndex == mValidIndex || validIndex == -1) {
        return;
    }
    removeDomNode();
    mValidIndex = validIndex;
    renderNode();
    getParentView()->requestLayout();
}


#pragma mark - Private
void QYIfDomNode::renderNode() {
    std::shared_ptr<QYBaseDomNode> validDomNode = getValidDomNode();
    //没有缓存，需要执行一遍performxxx
    if (!validDomNode) {
        validDomNode = std::make_shared<QYBaseDomNode>(shared_from_this(), mInfoList[mValidIndex], mPageCompContext);
        mCacheDomNodeMap[mValidIndex] = validDomNode;
        validDomNode->performExpandNodeTree();
        validDomNode->performExpandWidgetTree();
        validDomNode->performAttachParentView(mRealParentView);
        validDomNode->performApplyWidgetViewTreeProperties();
    }
    //有缓存，只需要把domnode、widget、view添加上去就行
    else {
        addChild(validDomNode);
        getWidget()->addChildWidget(validDomNode->getWidget());
        mRealParentView->addChildView(validDomNode->getView());
        validDomNode->performApplyWidgetViewTreeProperties();
    }
}

void QYIfDomNode::removeDomNode() {
    std::shared_ptr<QYBaseDomNode> validDomNode = getValidDomNode();
    if (validDomNode) {
        validDomNode->removeFromParentDomNode();
    }
}

int QYIfDomNode::calculateValidNodeIndex() {
    for (int i=0; i<mIfPropertyList.size(); i++) {
        std::shared_ptr<QYPropertyValue> proptyValue = mIfPropertyList[i];
        if (proptyValue->getKey().compare("qy:else") == 0) {
            return i;
        }
        if (proptyValue->getResult()->getBoolean()) {
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

std::shared_ptr<QYBaseDomNode> QYIfDomNode::getValidDomNode() {
    if (mCacheDomNodeMap.find(mValidIndex) == mCacheDomNodeMap.end()) {
        return nullptr;
    }
    return mCacheDomNodeMap[mValidIndex];
}

