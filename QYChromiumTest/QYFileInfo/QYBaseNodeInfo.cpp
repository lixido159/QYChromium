#include "QYBaseNodeInfo.h"

QYBaseNodeInfo::QYBaseNodeInfo() {
    
}

void QYBaseNodeInfo::addChildNodeInfo(std::shared_ptr<QYBaseNodeInfo> child) {
    this->childNodeInfoList.push_back(child);
    child->parent = weak_from_this();
}
