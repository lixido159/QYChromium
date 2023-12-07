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
#include "QYDom.h"
class QYComponentDomNode : public QYBaseDomNode{
public:
    QYComponentDomNode(QYBaseNodeInfo *info, std::shared_ptr<QYPageCompContext> context);

    virtual void performExpandNodeTree() override;
    virtual void performExpandWidgetTree() override;
private:
    std::unique_ptr<QYDom> mDom;
};
#endif /* QYComponentDomNode_hpp */
