//
//  QYComponentDomNode.hpp
//  QYView
//
//  Created by yinquan on 2023/12/1.
//

#ifndef QYComponentDomNode_hpp
#define QYComponentDomNode_hpp

#include <stdio.h>
#include "QYBaseDomNode.h"
class QYComponentDomNode : public QYBaseDomNode{
public:
    QYComponentDomNode(QYBaseNodeInfo *info);

    virtual void performExpandNodeTree() override;
    virtual void performExpandWidgetTree() override;

};
#endif /* QYComponentDomNode_hpp */
