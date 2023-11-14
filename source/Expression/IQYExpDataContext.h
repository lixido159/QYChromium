//
//  IQYExpDataContext.h
//  QYView
//
//  Created by yinquan on 2023/11/15.
//

#ifndef IQYExpDataContext_h
#define IQYExpDataContext_h

class IQYExpDataContext {
public:
    virtual bool getBoolForKey(std::string key) = 0;
    virtual std::string getStringForKey(std::string key) = 0;
    virtual double getNumberForKey(std::string key) = 0;
};


#endif /* Header_h */
