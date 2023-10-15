//
//  QYPropertySetter.hpp
//  QYView
//
//  Created by yinquan on 2023/10/12.
//

#ifndef QYPropertySetter_hpp
#define QYPropertySetter_hpp

#include <stdio.h>
#include <map>
#include "IQYBaseView.h"
#include "QYPropertyValue.h"


//#define Prop_Setter(key, func) QYPropertySetter::

class QYPropertySetter {
public:
    QYPropertySetter();
    void setProperty(IQYBaseView *view, QYPropertyValue *proptyValue);
private:
    std::map<std::string, void(*)(IQYBaseView *, QYPropertyValue *)> mPropFuncMap;
};
#endif /* QYPropertySetter_hpp */
