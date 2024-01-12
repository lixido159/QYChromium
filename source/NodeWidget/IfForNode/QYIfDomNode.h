//
//  QYIfDomNode.hpp
//  QYView
//
//  Created by yinquan on 2024/1/10.
//

#ifndef QYIfDomNode_hpp
#define QYIfDomNode_hpp

#include <stdio.h>
#include "QYBaseDomNode.h"
class QYIfDomNode : public QYBaseDomNode {
public:
    QYIfDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::vector<std::shared_ptr<QYBaseNodeInfo>> infoList, std::shared_ptr<QYPageCompContext> context);
private:
    std::vector<std::shared_ptr<QYBaseNodeInfo>> mInfoList;
};


#endif /* QYIfDomNode_hpp */
