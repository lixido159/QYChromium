

#include "QYBaseNodeInfo.h"
void QYBaseNodeInfo::addChildNodeInfo(QYBaseNodeInfo *child) {
    this->childNodeInfoList.push_back(child);
    child->parent = this;
}
