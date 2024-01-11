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
    virtual std::shared_ptr<QYBaseDomNode> createNode() override;
};

#endif /* QYIfDomNodeCreatorItem_hpp */
