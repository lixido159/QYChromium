//
//  main.m
//  SrcEncoder
//
//  Created by yinquan on 2023/12/9.
//
#include "fileUtil.h"
#include "QYPageParser.h"
#include <QYFileInfo/QYPageInfo.h>
#include <QYFileInfo/QYPageSerializer.h>
#include <iostream>
#include <filesystem>
#include <fstream>



template <class Archive>
void serialize(Archive& ar, QYPageInfo &page) {
    ar(page.jsStr, page.componentsMap);
}

template <class Archive>
void serialize(Archive& ar, QYBaseNodeInfo &node) {
    ar(node.name, node.properties, node.parent, node.childNodeInfoList);
}


std::string get_executable_path(const std::string& argv0) {
    std::filesystem::path executable_path = std::filesystem::absolute(argv0);
    return executable_path.parent_path().string();
}


int main(int argc, const char * argv[]) {
    std::string executable_dir = get_executable_path(argv[0]);
    std::string outputPath = executable_dir +"/output";
    createOutputDirIfNeed(outputPath);
    std::filesystem::path dir(executable_dir + "/src/pages");
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        std::cerr << "Directory does not exist or is not a directory: " << dir << std::endl;
        return 1;
    }

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_directory()) {
            std::string pageOutputPath = outputPath + "/";
            pageOutputPath.append(entry.path().filename());
            pageOutputPath.append(".page");
            std::shared_ptr<QYPageInfo> pageInfo = parsePageInfo(entry.path());
            pageInfo->jsStr = readFile(executable_dir + "/build/index.js");
            serializePageInfo(pageInfo, pageOutputPath);
        }
    }

    return 0;
}
