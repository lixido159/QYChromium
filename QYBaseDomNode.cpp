

#include "QYBaseDomNode.h"
#include "QYBaseWidget.h"
#include "QYViewCreateFactory.h"
#include "ui/views/background.h"
using namespace views;
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

std::unique_ptr<views::Background> strToColor(std::string str) {
    if (str == "red") {
        return CreateSolidBackground(SK_ColorRED);
    } else if (str == "black") {
        return CreateSolidBackground(SK_ColorBLACK);
    } else if (str == "green") {
        return CreateSolidBackground(SK_ColorGREEN);
    } else if (str == "blue") {
        return CreateSolidBackground(SK_ColorBLUE);
    } else if (str == "yellow") {
        return CreateSolidBackground(SK_ColorYELLOW);
    } else {
        return CreateSolidBackground(SK_ColorWHITE);
    }
}

void setProperty(std::string key, std::string value, QYBaseView *view) {
    printf("设置属性 %s %s\n", key.c_str(), value.c_str());
    if (key == "width") {
        view->mView->SetSize(gfx::Size(std::stoi(value), view->mView->height()));
    } else if (key == "height") {
        view->mView->SetSize(gfx::Size(view->mView->width(), std::stoi(value)));
    } else if (key == "left") {
        view->mView->SetX(std::stoi(value));
    } else if (key == "top") {
        view->mView->SetY(std::stoi(value));
    } else if (key == "background-color") {
        view->mView->SetBackground(strToColor(value));
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


