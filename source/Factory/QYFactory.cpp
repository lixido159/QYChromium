//
//  QYFactory.cpp
//  
//
//  Created by yinquan on 2023/7/2.
//

#include "QYFactory.h"
#include "QYBaseView.h"
#include "QYImageView.h"
#include "QYTextView.h"
#include "QYBaseCustomView.h"
#include "QYBaseCustomImageView.h"
#include "QYBaseCustomTextView.h"
#include "QYComponentDomNode.h"

extern QYBaseNodeInfo * parseFileToNodeInfo(const char *htmlFile);
IQYBaseView *createViewWithType(std::string type) {
    IQYBaseView *view;
    if (type.compare("view") == 0) {
        view = new QYBaseView;
    } else if(type.compare("image") == 0) {
        view = new QYImageView;
    } else if (type.compare("text") == 0){//view
        view = new QYTextView;
    } else {
        view = new QYBaseView;
    }
    return view;
}


QYBaseDomNode *createDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context) {
    QYBaseDomNode *domNode;
    if (info->name.compare("view") == 0 ||
        info->name.compare("image") == 0 ||
        info->name.compare("text") == 0) {
        domNode = new QYBaseDomNode(pageInfo, info, context);
    } else {
        std::shared_ptr<QYBaseNodeInfo> compInfo = pageInfo->componentsMap[info->name];
        info->addChildNodeInfo(compInfo);
        domNode = new QYComponentDomNode(pageInfo, info, context);
    }
    return domNode;
};
