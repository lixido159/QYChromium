//
//  QYComponentDomNode.cpp
//  QYView
//
//  Created by yinquan on 2023/12/1.
//

#include "QYComponentDomNode.h"
#include "QYFactory.h"
#include "QYBaseWidget.h"
#include "QYJSContext.h"
#include "QYJSValue.h"
QYComponentDomNode::QYComponentDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context): QYBaseDomNode(pageInfo, info) {
    std::shared_ptr<QYJSContext> jsContext = context->getJSContext();
    mPageCompContext.reset(new QYPageCompContext(jsContext));
    mPageCompContext->init();
    QYJSValue *global = jsContext->getGlobal();
    QYJSValue *qyValue = global->getValue(JSQYVar);
    QYJSValue *loaderValue = qyValue->getValue("compLoader");
    QYJSValue *compFuncValue = loaderValue->getValue(info->name);
    QYJSValue *compValue = compFuncValue->call(mPageCompContext->getContextJSValue()->getValue());
    mPageCompContext->setPageCompValue(compValue);

}

void QYComponentDomNode::performExpandNodeTree() {
    for(std::shared_ptr<QYBaseNodeInfo> childInfo : mNodeInfo->childNodeInfoList) {
        std::shared_ptr<QYBaseDomNode> node = createDomNode(mPageInfo, childInfo, mPageCompContext);
        addChild(node);
        node->performExpandNodeTree();
    }
}

void QYComponentDomNode::performExpandWidgetTree() {
    mWidget = std::make_shared<QYBaseWidget>(mPageCompContext, mNodeInfo);
    auto parent = mParent.lock();
    if (parent) {
        parent->getWidget()->addChildWidget(mWidget.get());
    }
    for(std::shared_ptr<QYBaseDomNode> node : mChildNodeList) {
        node->performExpandWidgetTree();
    }
    mDom.reset(new QYDom(mWidget));
    mPageCompContext->getContextJSValue()->getValue()->setValue("dom", mDom->getValue());
}

