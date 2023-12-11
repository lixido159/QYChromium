//
//  main.m
//  SrcEncoder
//
//  Created by yinquan on 2023/12/9.
//
#include "fileUtil.h"
#include "QYPageParser.h"
#import <QYFileInfo/QYPageInfo.h>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>

#include <cereal/archives/json.hpp>


template <class Archive>
void serialize(Archive& ar, QYBaseNodeInfo node) {
    ar(node.name, node.properties, node.parent, node.childNodeInfoList);
}
template <class Archive>
void serialize(Archive& ar, QYPageInfo page) {
    ar(page.jsStr, page.componentsMap);
}



int main(int argc, const char * argv[]) {
    createOutputDirIfNeed("./output");
    std::filesystem::path dir("./pages");
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        std::cerr << "Directory does not exist or is not a directory: " << dir << std::endl;
        return 1;
    }
    
    

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_directory()) {
            std::string outputPath = "./output/";
            outputPath.append(entry.path().filename());
            outputPath.append(".json");
            //反序列化
            std::shared_ptr<QYPageInfo> deInfo;
            std::ifstream input(outputPath.c_str());
            cereal::JSONInputArchive deArchive(input);
            deArchive(deInfo);
            
            std::string line;
                while (std::getline(input, line)) {
                    std::cout << line << std::endl;
                }

            printf("%s", line.c_str());
            //序列化
            std::shared_ptr<QYPageInfo> info = parsePageInfo(entry.path());
            std::ofstream os(outputPath.c_str());
            cereal::JSONOutputArchive archive(os);
            archive(info);
        }
    }

//    QYPageInfo *info = parsePageInfo();
    
//    std::ifstream ifs("out.cereal");
//    cereal::BinaryInputArchive a(ifs);
//    a(per);
//
//    std::ofstream os("out.cereal", std::ios::binary);
//    cereal::BinaryOutputArchive archive( os );
//    archive( *person );

    return 0;
}
