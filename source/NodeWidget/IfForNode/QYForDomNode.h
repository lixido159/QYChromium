//
//  QYForDomNode.hpp
//  QYView
//
//  Created by yinquan on 2024/2/4.
//

#ifndef QYForDomNode_hpp
#define QYForDomNode_hpp

#include <stdio.h>
#include "QYVirtualDomNode.h"

class QYForDomNode : public QYVirtualDomNode {
public:
    virtual void onDataUpdate(std::shared_ptr<QYPropertyValue> value) override;
};

#endif /* QYForDomNode_hpp */
