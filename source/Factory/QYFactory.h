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
IQYBaseView *createViewWithType(std::string type);
QYBaseWidget *createWidgetWithType(std::string type, std::shared_ptr<QYPageCompContext> context);

QYBaseDomNode *createDomNodeWithNodeInfo(QYBaseNodeInfo *info, std::shared_ptr<QYPageCompContext> context);
#endif /* QYFactory_hpp */
