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
    QYBaseDomNode *getRootNode() { return mRootNode.get(); }
    void beforeExecuteJS();
    void executeJS();
    void afterExecuteJS();
private:
    void registerDataInterface();
    
    std::shared_ptr<QYPageCompContext> mPageContext;
    std::shared_ptr<QYBaseDomNode> mRootNode;
    std::shared_ptr<QYJSContext> mJSContext;
    std::string mJSStr;
};


#endif /* QYPage_hpp */
