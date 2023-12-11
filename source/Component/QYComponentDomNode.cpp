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
QYComponentDomNode::QYComponentDomNode(QYBaseNodeInfo *info, std::shared_ptr<QYPageCompContext> context): QYBaseDomNode(info) {
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
        QYBaseDomNode *node = createDomNodeWithNodeInfo(childInfo, mPageCompContext);
        addChild(node);
        node->performExpandNodeTree();
    }
}

void QYComponentDomNode::performExpandWidgetTree() {
    mWidget = std::make_shared<QYBaseWidget>(mPageCompContext, mNodeInfo->name);
    if (mParent) {
        mParent->getWidget()->addChildWidget(mWidget.get());
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performExpandWidgetTree();
    }
    mDom.reset(new QYDom(mWidget));
    mPageCompContext->getContextJSValue()->getValue()->setValue("dom", mDom->getValue());
}

