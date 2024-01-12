//
//  QYIfDomNode.cpp
//  QYView
//
//  Created by yinquan on 2024/1/10.
//

#include "QYIfDomNode.h"
QYIfDomNode::QYIfDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::vector<std::shared_ptr<QYBaseNodeInfo>> infoList, std::shared_ptr<QYPageCompContext> context): QYBaseDomNode(pageInfo, nullptr, context), mInfoList(infoList) {
    
}
