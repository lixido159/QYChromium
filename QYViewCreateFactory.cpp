//
//  QYViewCreateFactory.cpp
//  
//
//  Created by yinquan on 2023/7/2.
//

#include "QYViewCreateFactory.h"
#include "ui/views/controls/label.h"
#include "ui/views/controls/image_view.h"
#include "ui/views/controls/button/label_button.h"
QYBaseView *createViewWithNodeInfo(QYBaseNodeInfo *info) {
    QYBaseView *view = new QYBaseView;
    if (info->name.compare("text")) {
        view->mView = new views::Label();
    } else if(info->name.compare("image")) {
        view->mView = new views::ImageView();
    } else if(info->name.compare("button")) {
        view->mView = new views::LabelButton();
    } else {//view
        view->mView = new views::View();
    }
    return view;
}
