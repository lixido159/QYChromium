//
//  QYCommonDomNodeCreatorItem.cpp
//  QYView
//
//  Created by yinquan on 2024/1/12.
//

#include "QYCommonDomNodeCreatorItem.h"
#include "QYFactory.h"

QYCommonDomNodeCreatorItem::QYCommonDomNodeCreatorItem(std::shared_ptr<QYBaseNodeInfo> nodeInfo):mNodeInfo(nodeInfo) {
    
}

std::shared_ptr<QYBaseDomNode> QYCommonDomNodeCreatorItem::createNode(std::shared_ptr<QYBaseDomNode> parent, std::shared_ptr<QYPageCompContext> context) {
    return createDomNode(parent, mNodeInfo, context);
}
