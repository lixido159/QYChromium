//
//  QYPage.cpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#include "QYPage.h"
QYPage::QYPage(QYBaseDomNode *rootNode, std::string jsStr):mRootNode(rootNode), mJSStr(jsStr) {
    mJSContext = new QYJSContext();
    mPageContext.reset(new QYPageCompContext());
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

void QYPage::registerDataInterface() {
    mPageData->setFunction("update", [this](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue * {
        mPageContext->notifyDataUpdate();
        return nullptr;
    });
}

void QYPage::executeJS() {
    mJSContext->executeJS(mJSStr.c_str());
    QYJSValue *global = mJSContext->getGlobal();
    QYJSValue *qyValue = global->getValue(JSQYVar);
    mPageData = std::shared_ptr<QYJSValue>(mJSContext->newObject());
    mPageContext->setDataValue(mPageData);
    registerDataInterface();
    qyValue->getValue("entry")->call(mPageData.get());
}


void QYPage::afterExecuteJS() {
    
}
