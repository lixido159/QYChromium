//
//  Header.h
//  QYView
//
//  Created by yinquan on 2023/11/9.
//

#ifndef Header_h
#define Header_h
class QYPropertyValue;

class IQYPropertyValueObserver {
public:
    virtual void onDataUpdate(QYPropertyValue *value) = 0;
};


#endif /* Header_h */
