//
//  QYCommonDomNodeCreatorItem.hpp
//  QYView
//
//  Created by yinquan on 2024/1/12.
//

#ifndef QYCommonDomNodeCreatorItem_hpp
#define QYCommonDomNodeCreatorItem_hpp

#include <stdio.h>
#include "IQYDomNodeCreatorItem.h"

class QYCommonDomNodeCreatorItem : public IQYDomNodeCreatorItem {
public:
    QYCommonDomNodeCreatorItem(std::shared_ptr<QYBaseNodeInfo> nodeInfo);
    virtual std::shared_ptr<QYBaseDomNode> createNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYPageCompContext> context) override;
private:
    std::shared_ptr<QYBaseNodeInfo> mNodeInfo;
};

#endif /* QYCommonDomNodeCreatorItem_hpp */
