//
//  QYPage.cpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#include "QYPage.h"
#include "QYContextJSValue.h"

QYPage::QYPage(QYBaseDomNode *rootNode, std::string jsStr):mRootNode(rootNode), mJSStr(jsStr) {
    mJSContext = std::make_shared<QYJSContext>();
    mJSContext->registerContextGlobalObject();
    mPageContext.reset(new QYPageCompContext(mJSContext));
    mPageContext->init();
    rootNode->setContext(mPageContext);
}

QYPage::~QYPage() {
    
}

void QYPage::init() {
    beforeExecuteJS();
    executeJS();
    afterExecuteJS();

    mRootNode->performExpandNodeTree();
    mRootNode->performExpandWidgetTree();
    mRootNode->performExpandWidgetViewTree();
    mRootNode->performApplyWidgetViewTreeProperties();
}

void QYPage::beforeExecuteJS() {
    
}

void QYPage::executeJS() {
    mJSContext->executeJS(mJSStr.c_str());
    QYJSValue *global = mJSContext->getGlobal();
    QYJSValue *qyValue = global->getValue(JSQYVar);
    
    QYJSValue *pageValue = qyValue->getValue("entry")->call(mPageContext->getContextJSValue()->getValue());
    mPageContext->setPageCompValue(pageValue);
}


void QYPage::afterExecuteJS() {
    
}
