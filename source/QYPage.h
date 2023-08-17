//
//  QYPage.hpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#ifndef QYPage_hpp
#define QYPage_hpp
#include "QYBaseDomNode.h"

class QYPage {
public:
    QYPage(QYBaseDomNode *rootNode);
    void init();
    QYBaseDomNode *getRootNode() { return mRootNode; }
private:
    QYBaseDomNode *mRootNode;
    
};


#endif /* QYPage_hpp */
