//
//  QYIfDomNode.cpp
//  QYView
//
//  Created by yinquan on 2024/1/10.
//

#include "QYIfDomNode.h"

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

QYIfDomNode::QYIfDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::vector<std::shared_ptr<QYBaseNodeInfo>> infoList, std::shared_ptr<QYPageCompContext> context): QYBaseDomNode(pageInfo, nullptr, context), mInfoList(infoList) {
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
    int validIndex = calculateValidIndex();
    if (validIndex == -1) {
        return;
    }
    mNodeInfo = mInfoList[validIndex];

}

void QYIfDomNode::performExpandNodeTree() {
    if (mNodeInfo) {
        QYBaseDomNode::performExpandNodeTree();
    }
}

void QYIfDomNode::performExpandWidgetTree() {
    if (mNodeInfo) {
        QYBaseDomNode::performExpandWidgetTree();
    }
}

void QYIfDomNode::performExpandWidgetViewTree() {
    if (mNodeInfo) {
        QYBaseDomNode::performExpandWidgetTree();
    }
}



void QYIfDomNode::performApplyWidgetViewTreeProperties() {
    if (mNodeInfo) {
        QYBaseDomNode::performApplyWidgetViewTreeProperties();
    }
}

int QYIfDomNode::calculateValidIndex() {
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

void QYIfDomNode::onDataUpdate(std::shared_ptr<QYPropertyValue> value) {
    int index = calculateValidIndex();
    
}
