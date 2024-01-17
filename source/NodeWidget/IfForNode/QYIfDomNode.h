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
    QYIfDomNode(std::shared_ptr<QYBaseDomNode> parent,
                std::vector<std::shared_ptr<QYBaseNodeInfo>> infoList, std::shared_ptr<QYPageCompContext> context);
    
    virtual void performExpandNodeTree() override;
    virtual void performExpandWidgetTree() override;
    virtual void performAttachParentView(std::shared_ptr<IQYBaseView> parentView) override;
    virtual void performApplyWidgetViewTreeProperties() override;
    virtual void onDataUpdate(std::shared_ptr<QYPropertyValue> value) override;
    
private:
    int calculateValidNodeIndex();
    void renderNode();
    void removeDomNode();
    void addDomNode();
    void init();
    std::shared_ptr<QYBaseDomNode> getValidDomNode();
private:
    std::vector<std::shared_ptr<QYBaseNodeInfo>> mInfoList;
    std::vector<std::shared_ptr<QYPropertyValue>> mIfPropertyList;
    std::map<int, std::shared_ptr<QYBaseDomNode>> mCacheDomNodeMap;
    std::shared_ptr<IQYBaseView> mRealParentView;
    int mValidIndex = -1;
};


#endif /* QYIfDomNode_hpp */
