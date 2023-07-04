
#ifndef QYBaseNodeInfo_hpp
#define QYBaseNodeInfo_hpp

#include "CommonHeader.h"

///XML信息
class QYBaseNodeInfo {
public:
    //类型名，比如<view>，这里就是view
    std::string name = "";
    //属性名
    std::map<std::string, std::string> properties;
    //父节点
    QYBaseNodeInfo *parent = nullptr;
    //子节点
    std::vector<QYBaseNodeInfo *> childNodeInfoList;
    //添加子节点
    void addChildNodeInfo(QYBaseNodeInfo *info);
};


#endif /* QYBaseNodeInfo_hpp */
