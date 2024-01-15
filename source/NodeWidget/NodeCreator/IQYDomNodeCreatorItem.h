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
    virtual std::shared_ptr<QYBaseDomNode> createNode(std::shared_ptr<QYBaseDomNode> parent, std::shared_ptr<QYPageCompContext> context) = 0;
};

#endif /* IQYDomNodeCreatorItem_h */
