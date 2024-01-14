//
//  QYIfDomNode.hpp
//  QYView
//
//  Created by yinquan on 2024/1/10.
//

#ifndef QYIfDomNode_hpp
#define QYIfDomNode_hpp

#include <stdio.h>
#include "QYBaseDomNode.h"
#include "QYPropertyValue.h"
class QYIfDomNode : public QYBaseDomNode {
public:
    QYIfDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::vector<std::shared_ptr<QYBaseNodeInfo>> infoList, std::shared_ptr<QYPageCompContext> context);
    
    virtual void performExpandNodeTree() override;
    virtual void performExpandWidgetTree() override;
    virtual void performExpandWidgetViewTree() override;
    virtual void performApplyWidgetViewTreeProperties() override;
    virtual void onDataUpdate(std::shared_ptr<QYPropertyValue> value) override;
    
    int calculateValidIndex();
private:
    std::vector<std::shared_ptr<QYBaseNodeInfo>> mInfoList;
    std::vector<std::shared_ptr<QYPropertyValue>> mIfPropertyList;
};


#endif /* QYIfDomNode_hpp */
