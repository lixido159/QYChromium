//
//  QYDom.hpp
//  QYView
//
//  Created by yinquan on 2023/12/7.
//

#ifndef QYDom_hpp
#define QYDom_hpp

#include <stdio.h>
#include "QYBaseWidget.h"

//Dom
class QYDom {
    QYDom(QYBaseWidget *widget);
private:
    QYBaseWidget *mWidget;
};


#endif /* QYDom_hpp */
