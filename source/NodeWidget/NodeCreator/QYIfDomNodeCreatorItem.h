//
//  QYIfDomNodeCreatorItem.hpp
//  QYView
//
//  Created by yinquan on 2024/1/12.
//

#ifndef QYIfDomNodeCreatorItem_hpp
#define QYIfDomNodeCreatorItem_hpp

#include <stdio.h>

#include "IQYDomNodeCreatorItem.h"
class QYIfDomNodeCreatorItem : public IQYDomNodeCreatorItem {
public:
    QYIfDomNodeCreatorItem(std::vector<std::shared_ptr<QYBaseNodeInfo>> nodeInfoList);
    virtual std::shared_ptr<QYBaseDomNode> createNode(std::shared_ptr<QYBaseDomNode> parent, std::shared_ptr<QYPageCompContext> context) override;
private:
    std::vector<std::shared_ptr<QYBaseNodeInfo>> mNodeInfoList;
};

#endif /* QYIfDomNodeCreatorItem_hpp */
