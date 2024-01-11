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
    virtual std::shared_ptr<QYBaseDomNode> createNode() override;
};

#endif /* QYCommonDomNodeCreatorItem_hpp */
