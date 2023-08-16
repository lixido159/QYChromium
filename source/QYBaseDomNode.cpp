

#include "QYBaseDomNode.h"
#include "QYBaseWidget.h"
#include "QYViewCreateFactory.h"


QYBaseDomNode::QYBaseDomNode(QYBaseNodeInfo *info): mNodeInfo(info) {
    
}
void QYBaseDomNode::addChild(QYBaseDomNode * child) {
    this->mChildNodeList.push_back(child);
    child->mParent = this;
}

void QYBaseDomNode::performExpandNodeTree() {
    for(QYBaseNodeInfo *childInfo : mNodeInfo->childNodeInfoList) {
        QYBaseDomNode *node = new QYBaseDomNode(childInfo);
        addChild(node);
        node->performExpandNodeTree();
    }
}

void QYBaseDomNode::performExpandWidgetTree() {
    mWidget = new QYBaseWidget;
    if (mParent) {
        mParent->mWidget->addChild(mWidget);
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performExpandWidgetTree();
    }
}

void QYBaseDomNode::performExpandWidgetViewTree() {
    QYBaseView *view = createViewWithNodeInfo(mNodeInfo);
    mWidget->mView = view;
    if (mWidget->mParent) {
        mWidget->mParent->mView->addChild(view);
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performExpandWidgetViewTree();
    }
}

unsigned int strToColor(std::string str) {
    if (str == "red") {
        return QYColor(255, 0, 0, 255);
    } else if (str == "black") {
        return QYColor(0, 0, 0, 255);
    } else if (str == "green") {
        return QYColor(0, 255, 0, 255);
    } else if (str == "blue") {
        return QYColor(0, 0, 255, 255);
    } else if (str == "yellow") {
        return QYColor(255, 255, 0, 255);
    } else if (str == "gray") {
        return QYColor(128, 128, 128, 255);
    } else {
        return QYColor(255, 255, 255, 255);
    }
}

void setProperty(std::string key, std::string value, QYBaseView *view) {
    printf("设置属性 %s %s\n", key.c_str(), value.c_str());
    if (key == "width") {
        view->mView->setWidth(std::stoi(value));
    } else if (key == "height") {
        view->mView->setHeight(std::stoi(value));
    } else if (key == "left") {
        view->mView->setX(std::stoi(value));
    } else if (key == "top") {
        view->mView->setY(std::stoi(value));
    } else if (key == "background-color") {
        unsigned int color = strToColor(value);
        int r = QYColorRGBA_R(color);
        int g = QYColorRGBA_G(color);
        int b = QYColorRGBA_B(color);
        int a = QYColorRGBA_A(color);
        view->mView->setBackgroundColor(QYColorRGBA_R(color), QYColorRGBA_G(color), QYColorRGBA_B(color), QYColorRGBA_A(color));
    }
}

void QYBaseDomNode::performApplyWidgetViewTreeProperties() {
    std::map<std::string, std::string>::iterator iter;
    for (iter = mNodeInfo->properties.begin(); iter != mNodeInfo->properties.end(); iter++) {
        setProperty(iter->first, iter->second, mWidget->mView);
    }
    for(QYBaseDomNode *node : mChildNodeList) {
        node->performApplyWidgetViewTreeProperties();
    }
}


void *QYBaseDomNode::nativeView() {
    return mWidget->mView->mView;
}


