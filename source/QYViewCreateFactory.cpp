//
//  QYViewCreateFactory.cpp
//  
//
//  Created by yinquan on 2023/7/2.
//

#include "QYViewCreateFactory.h"
#include "QYBaseCustomView.h"
#include "QYBaseCustomImageView.h"
#include "QYBaseCustomTextView.h"
QYBaseView *createViewWithNodeInfo(QYBaseNodeInfo *info) {
    QYBaseView *view = new QYBaseView;
    if (info->name.compare("text")) {
        view->mView = new QYBaseCustomImageView();
    } else if(info->name.compare("image")) {
        view->mView = new QYBaseCustomImageView();
    } else {//view
        view->mView = new QYBaseCustomView();
    }
    return view;
}
