//
//  QYPage.cpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#include "QYPage.h"
#include "QYContextJSValue.h"

QYPage::QYPage(std::shared_ptr<QYPageInfo> pageInfo):mPageInfo(pageInfo) {
    mRootNode = std::make_shared<QYBaseDomNode>(pageInfo, pageInfo->componentsMap["index"]);
    mJSStr = pageInfo->jsStr;
    mJSContext = std::make_shared<QYJSContext>();
    mJSContext->registerContextGlobalObject();
    mPageContext.reset(new QYPageCompContext(mJSContext));
    mPageContext->init();
    mRootNode->setContext(mPageContext);
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
    mDom.reset(new QYDom(mRootNode->getWidget()));
    mPageContext->getContextJSValue()->getValue()->setValue("dom", mDom->getValue());
    executePageEntryJS();
    
}

void QYPage::beforeExecuteJS() {
    
}

void QYPage::executeJS() {
    mJSContext->executeJS(mJSStr.c_str());
    
}

void QYPage::executePageEntryJS() {
    QYJSValue *global = mJSContext->getGlobal();
    QYJSValue *qyValue = global->getValue(JSQYVar);
    QYJSValue *pageValue = qyValue->getValue("entry")->call(mPageContext->getContextJSValue()->getValue());
    mPageContext->setPageCompValue(pageValue);

}


void QYPage::afterExecuteJS() {
    
}

void *QYPage::getNativeView() {
    return mRootNode->getNativeView();
}

void QYPage::onSizeChange() {
    mRootNode->getWidget()->onSizeChange();
}
