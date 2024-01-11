//
//  IQYDomNodeCreatorItem.h
//  QYView
//
//  Created by yinquan on 2024/1/12.
//

#ifndef IQYDomNodeCreatorItem_h
#define IQYDomNodeCreatorItem_h

#include "QYBaseDomNode.h"

class IQYDomNodeCreatorItem {
public:
    virtual std::shared_ptr<QYBaseDomNode> createNode();
};

#endif /* IQYDomNodeCreatorItem_h */
