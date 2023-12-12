//
//  fileUtil.hpp
//  QYView
//
//  Created by yinquan on 2023/9/12.
//

#ifndef fileUtil_hpp
#define fileUtil_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <filesystem>


void traverseDir(std::string name, std::string extension, std::vector<std::string> &fileNames);
void createOutputDirIfNeed(std::string name);
std::string readFile(std::string fileName);
std::string filePathToCompName(std::string path, std::string prefix);
#endif /* fileUtil_hpp */
