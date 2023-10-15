//
//  QYViewCreateFactory.cpp
//  
//
//  Created by yinquan on 2023/7/2.
//

#include "QYViewCreateFactory.h"
#include "QYBaseView.h"
#include "QYImageView.h"
#include "QYTextView.h"
#include "QYBaseCustomView.h"
#include "QYBaseCustomImageView.h"
#include "QYBaseCustomTextView.h"
IQYBaseView *createViewWithNodeInfo(QYBaseNodeInfo *info) {
    IQYBaseView *view;
    if (info->name.compare("text")) {
        view = new QYBaseView;
        view->setCustomView(new QYBaseCustomImageView());
    } else if(info->name.compare("image")) {
        view = new QYImageView;
        view->setCustomView(new QYBaseCustomImageView());
    } else {//view
        view = new QYTextView;
        view->setCustomView(new QYBaseCustomView());
    }
    return view;
}
