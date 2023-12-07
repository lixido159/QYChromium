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
    mContext.reset(new QYPageCompContext(jsContext));
    mContext->init();
    QYJSValue *global = jsContext->getGlobal();
    QYJSValue *qyValue = global->getValue(JSQYVar);
    QYJSValue *loaderValue = qyValue->getValue("compLoader");
    QYJSValue *compFuncValue = loaderValue->getValue(info->name);
    QYJSValue *compValue = compFuncValue->call(mContext->getContextJSValue()->getValue());
    mContext->setPageCompValue(compValue);

}

void QYComponentDomNode::performExpandNodeTree() {
    for(QYBaseNodeInfo *childInfo : mNodeInfo->childNodeInfoList) {
        QYBaseDomNode *node = createDomNodeWithNodeInfo(childInfo, mContext);
        addChild(node);
        node->performExpandNodeTree();
    }
}

void QYComponentDomNode::performExpandWidgetTree() {
    mWidget = std::make_shared<QYBaseWidget>(mContext, mNodeInfo->name);
    if (mParent) {
        mParent->mWidget->addChildWidget(mWidget.get());
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performExpandWidgetTree();
    }
}

