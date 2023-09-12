//
//  fileUtil.cpp
//  QYView
//
//  Created by yinquan on 2023/9/12.
//

#include "fileUtil.h"
#include <iostream>
#include <fstream>

std::string readFile(const char *fileName) {
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string content((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));
        file.close();
        return content;
    } else {
        std::cout << "Unable to open file" << std::endl;
        return "";
    }
}
