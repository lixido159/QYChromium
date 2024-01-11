//
//  QYFactory.hpp
//  
//
//  Created by yinquan on 2023/7/2.
//

#ifndef QYFactory_hpp
#define QYFactory_hpp

#include "IQYBaseView.h"
#include "QYBaseDomNode.h"
#include "IQYDomNodeCreatorItem.h"
IQYBaseView *createViewWithType(std::string type);
QYBaseWidget *createWidgetWithType(std::string type, std::shared_ptr<QYPageCompContext> context);

QYBaseDomNode *createDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo>, std::shared_ptr<QYPageCompContext> context);

std::vector<std::shared_ptr<IQYDomNodeCreatorItem>> createDomNodeCreatorItems(std::vector<std::shared_ptr<QYBaseNodeInfo>> childInfos);
#endif /* QYFactory_hpp */
