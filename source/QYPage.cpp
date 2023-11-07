//
//  QYPage.cpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#include "QYPage.h"
QYPage::QYPage(QYBaseDomNode *rootNode, std::string jsStr):mRootNode(rootNode), mJSStr(jsStr) {
    mJSContext = new QYJSContext();
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

void registerDataInterface(QYJSValue *data) {
    data->setFunction("update", [](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue * {
        printf("%s: %s", paramsValue->getValue(0)->toString().c_str(), paramsValue->getValue(1)->toString().c_str());
        return nullptr;
    });
}

void QYPage::executeJS() {
    mJSContext->executeJS(mJSStr.c_str());
    QYJSValue *global = mJSContext->getGlobal();
    QYJSValue *qyValue = global->getValue(JSQYVar);
    mPageData = mJSContext->newObject();
    registerDataInterface(mPageData);
    qyValue->getValue("entry")->call(mPageData);
    
}


void QYPage::afterExecuteJS() {
    
}
