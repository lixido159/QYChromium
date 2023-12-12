//
//  QYPageInfo.hpp
//  QYFileInfo
//
//  Created by yinquan on 2023/12/9.
//

#ifndef QYPageInfo_hpp
#define QYPageInfo_hpp

#include "QYBaseNodeInfo.h"

class QYPageInfo : public std::enable_shared_from_this<QYPageInfo>{
public:
    QYPageInfo();
    //js
    std::string jsStr;
    //每个组件对应的html，入口的是key:index
    std::map<std::string, std::shared_ptr<QYBaseNodeInfo>> componentsMap;
    void writeToFile(std::string filePath);
    static QYPageInfo *readFromFile(std::string filePath);
};

#endif /* QYPageInfo_hpp */
