//
//  fileUtil.cpp
//  QYView
//
//  Created by yinquan on 2023/9/12.
//

#include "fileUtil.h"
#include <iostream>
#include <fstream>

std::string readFile(std::string fileName) {
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

//创建产物目录
void createOutputDirIfNeed(std::string name) {
    std::filesystem::path dir(name);
    if (std::filesystem::exists(dir)) {
        std::cout << "Directory exists.\n";
    }
    else {
        if (std::filesystem::create_directory(dir))
            std::cout << "Directory created successfully.\n";
        else
            std::cout << "Failed to create directory.\n";
    }
}


void traverseDir(std::string name, std::string extension, std::vector<std::string> &fileNames) {
    std::filesystem::path dir(name);
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        std::cerr << "Directory does not exist or is not a directory: " << dir << std::endl;
        return;
    }
    for (const auto& entry : std::filesystem::recursive_directory_iterator(dir)) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            fileNames.push_back(entry.path());
            std::cout << "File: " << entry.path().relative_path() << std::endl;
        }
    }
}

void replaceString(std::string &str, std::string replacedString, std::string replaceString) {
    size_t start_pos = str.find(replacedString);
    if(start_pos != std::string::npos) {
        str.replace(start_pos, replacedString.length(), replaceString);
    }
}

//./pages/qycomp/test.html -> qycomp-test
std::string filePathToCompName(std::string path) {
    replaceString(path, "./pages/", "");
    replaceString(path, ".html", "");
    replaceString(path, "/", "-");
    return path;
}

