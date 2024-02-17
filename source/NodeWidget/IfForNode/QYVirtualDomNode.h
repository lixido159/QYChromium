//
//  QYVirtualDomNode.hpp
//  QYView
//
//  Created by yinquan on 2024/2/4.
//

#ifndef QYVirtualDomNode_hpp
#define QYVirtualDomNode_hpp

#include <stdio.h>
#include "QYBaseDomNode.h"
class QYVirtualDomNode : public QYBaseDomNode {
public:
    QYVirtualDomNode(std::shared_ptr<QYBaseDomNode> parent, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context);
    virtual void performExpandNodeTree() override;
    virtual void performExpandWidgetTree() override;
    virtual void performAttachParentView(std::shared_ptr<IQYBaseView> parentView) override;
    virtual void performApplyWidgetViewTreeProperties() override;
protected:
    std::shared_ptr<IQYBaseView> mRealParentView;

};



#endif /* QYVirtualDomNode_hpp */
