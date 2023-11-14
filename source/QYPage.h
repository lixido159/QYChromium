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
class QYPage {
public:
    QYPage(QYBaseDomNode *rootNode, std::string jsStr);
    ~QYPage();
    void init();
    QYBaseDomNode *getRootNode() { return mRootNode; }
    void beforeExecuteJS();
    void executeJS();
    void afterExecuteJS();
private:
    void registerDataInterface();
    
    std::shared_ptr<QYPageCompContext> mPageContext;
    QYBaseDomNode *mRootNode = nullptr;
    QYJSContext *mJSContext = nullptr;
    std::shared_ptr<QYJSValue> mPageData = nullptr;
    std::string mJSStr;
};


#endif /* QYPage_hpp */
