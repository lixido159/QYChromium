//
//  QYPage.hpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#ifndef QYPage_hpp
#define QYPage_hpp
#include "QYBaseDomNode.h"
#include "QYJSContext.h"
#include "QYPageCompContext.h"
#include "QYDom.h"
#include <QYFileInfo/QYPageInfo.h>
class QYPage {
public:
    QYPage(std::shared_ptr<QYPageInfo> pageInfo);
    ~QYPage();
    void init();
    QYBaseDomNode *getRootNode() { return mRootNode.get(); }
    void beforeExecuteJS();
    void executeJS();
    void afterExecuteJS();
    void *getNativeView();
    void onSizeChange();
private:
    void executePageEntryJS();
    void registerDataInterface();
    std::shared_ptr<QYPageCompContext> mPageContext;
    std::shared_ptr<QYBaseDomNode> mRootNode;
    std::shared_ptr<QYJSContext> mJSContext;
    std::shared_ptr<QYPageInfo> mPageInfo;
    std::unique_ptr<QYDom> mDom;
    std::string mJSStr;
};


#endif /* QYPage_hpp */
