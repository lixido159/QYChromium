//
//  IQYExpDataContext.h
//  QYView
//
//  Created by yinquan on 2023/11/15.
//

#ifndef IQYExpDataContext_h
#define IQYExpDataContext_h
#include "QYExpResult.h"

class IQYExpDataContext {
public:
    virtual std::shared_ptr<QYExpResult> getResultForKey(std::string key) = 0;
    virtual QYExpResultType getTypeForKey(std::string key) = 0;
    virtual bool hasValueForKey(std::string key) = 0;
    
    
};


#endif /* Header_h */
