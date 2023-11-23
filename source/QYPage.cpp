//
//  QYPage.cpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#include "QYPage.h"
QYPage::QYPage(QYBaseDomNode *rootNode, std::string jsStr):mRootNode(rootNode), mJSStr(jsStr) {
    mJSContext = std::make_shared<QYJSContext>();
    mJSContext->registerContextGlobalObject();
    mPageContext.reset(new QYPageCompContext(mJSContext));
    rootNode->setContext(mPageContext);
}

QYPage::~QYPage() {
    
}

void QYPage::init() {
    mRootNode->performExpandNodeTree();
    mRootNode->performExpandWidgetTree();
    mRootNode->performExpandWidgetViewTree();
    mRootNode->performApplyWidgetViewTreeProperties();
    beforeExecuteJS();
    executeJS();
    afterExecuteJS();
}

void QYPage::beforeExecuteJS() {
    
}

void QYPage::executeJS() {
    mJSContext->executeJS(mJSStr.c_str());
    QYJSValue *global = mJSContext->getGlobal();
    QYJSValue *qyValue = global->getValue(JSQYVar);
    QYJSValue *dataValue = mJSContext->newObject();
    mPageContext->registerDataInterface(dataValue);
    QYJSValue *pageValue = qyValue->getValue("entry")->call(dataValue);
    mPageContext->setPageCompValue(pageValue);
    
}


void QYPage::afterExecuteJS() {
    
}
