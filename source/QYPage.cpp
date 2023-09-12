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

void QYPage::executeJS() {
    mJSContext->executeJS(mJSStr.c_str());
}

void QYPage::afterExecuteJS() {
    
}
