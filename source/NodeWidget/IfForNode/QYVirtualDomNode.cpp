//
//  QYVirtualDomNode.cpp
//  QYView
//
//  Created by yinquan on 2024/2/4.
//

#include "QYVirtualDomNode.h"
#include "QYBaseWidget.h"

QYVirtualDomNode::QYVirtualDomNode(std::shared_ptr<QYBaseDomNode> parent, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context):QYBaseDomNode(parent, info, context) {
    
}


void QYVirtualDomNode::performExpandNodeTree() {
    auto parent = mParent.lock();
    if (parent) {
        parent->addChild(shared_from_this());
    }
}

void QYVirtualDomNode::performExpandWidgetTree() {
    mWidget = std::make_shared<QYBaseWidget>(mPageCompContext, getNodeType());
    auto parent = mParent.lock();
    if (parent) {
        parent->getWidget()->addChildWidget(mWidget);
    }
}

void QYVirtualDomNode::performAttachParentView(std::shared_ptr<IQYBaseView> parentView) {
    mRealParentView = parentView;
}

void QYVirtualDomNode::performApplyWidgetViewTreeProperties() {
    
}

