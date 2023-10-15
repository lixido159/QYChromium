//
//  QYViewCreateFactory.hpp
//  
//
//  Created by yinquan on 2023/7/2.
//

#ifndef QYViewCreateFactory_hpp
#define QYViewCreateFactory_hpp

#include "IQYBaseView.h"
#include "QYBaseNodeInfo.h"
IQYBaseView *createViewWithNodeInfo(QYBaseNodeInfo *info);

#endif /* QYViewCreateFactory_hpp */
