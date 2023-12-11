
#ifndef QYBaseNodeInfo_hpp
#define QYBaseNodeInfo_hpp

#include <string>
#include <map>
#include <vector>
#include <memory>

///XML信息
class QYBaseNodeInfo : public std::enable_shared_from_this<QYBaseNodeInfo>{
public:
    //类型名，比如<view>，这里就是view
    std::string name = "";
    //属性名
    std::map<std::string, std::string> properties;
    //父节点
    std::weak_ptr<QYBaseNodeInfo> parent;
    //子节点
    std::vector<std::shared_ptr<QYBaseNodeInfo>> childNodeInfoList;
    //添加子节点
    void addChildNodeInfo(std::shared_ptr<QYBaseNodeInfo> info);
};


#endif /* QYBaseNodeInfo_hpp */
