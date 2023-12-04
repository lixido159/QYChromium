//
//  QYComponentDomNode.cpp
//  QYView
//
//  Created by yinquan on 2023/12/1.
//

#include "QYComponentDomNode.h"
#include "QYFactory.h"
#include "QYBaseWidget.h"
QYComponentDomNode::QYComponentDomNode(QYBaseNodeInfo *info): QYBaseDomNode(info) {
//    mContext.reset(new QYPageCompContext(mJSContext));
}

void QYComponentDomNode::performExpandNodeTree() {
    for(QYBaseNodeInfo *childInfo : mNodeInfo->childNodeInfoList) {
        QYBaseDomNode *node = createDomNodeWithNodeInfo(childInfo, mContext);
        addChild(node);
        node->performExpandNodeTree();
    }
}

void QYComponentDomNode::performExpandWidgetTree() {
    mWidget = new QYBaseWidget(mContext, mNodeInfo->name);
    if (mParent) {
        mParent->mWidget->addChildWidget(mWidget);
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performExpandWidgetTree();
    }
}

