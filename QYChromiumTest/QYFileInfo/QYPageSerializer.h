//
//  QYPageSerializer.hpp
//  QYFileInfo
//
//  Created by yinquan on 2023/12/12.
//

#ifndef QYPageSerializer_hpp
#define QYPageSerializer_hpp
#include "QYPageInfo.h"

#include <stdio.h>
#include <memory>
void serializePageInfo(std::shared_ptr<QYPageInfo> pageInfo, std::string outputPath);
std::shared_ptr<QYPageInfo> deserializePageInfo(std::string inputPath);


#endif /* QYPageSerializer_hpp */
