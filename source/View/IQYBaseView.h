//
//  IQYBaseView.h
//  QYView
//
//  Created by yinquan on 2023/10/15.
//

#ifndef IQYBaseView_h
#define IQYBaseView_h

#include "IQYBaseCustomBaseView.h"
#include <vector>

class IQYBaseView {
public:
    virtual void addChildView(IQYBaseView *child) = 0;
    
    virtual IQYBaseView *getParentView() = 0;
    virtual void setParentView(IQYBaseView *parentView) = 0;
    
    virtual IQYBaseCustomBaseView *getCustomView() = 0;
    virtual void setCustomView(IQYBaseCustomBaseView *customView) = 0;
};

#endif /* IQYBaseView_h */
