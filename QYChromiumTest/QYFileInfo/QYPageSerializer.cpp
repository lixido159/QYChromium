//
//  QYPageSerializer.cpp
//  QYFileInfo
//
//  Created by yinquan on 2023/12/12.
//

#include "QYPageSerializer.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>


template <class Archive>
void serialize(Archive& ar, QYPageInfo &page) {
    ar(page.jsStr, page.componentsMap);
}

template <class Archive>
void serialize(Archive& ar, QYBaseNodeInfo &node) {
    ar(node.name, node.properties, node.parent, node.childNodeInfoList);
}


void serializePageInfo(std::shared_ptr<QYPageInfo> pageInfo, std::string outputPath) {
    //序列化
    std::ofstream os(outputPath.c_str());
    cereal::BinaryOutputArchive archive(os);
    archive(pageInfo);
}

std::shared_ptr<QYPageInfo> deserializePageInfo(std::string inputPath) {
    //反序列化
    std::shared_ptr<QYPageInfo> deInfo;
    std::ifstream input(inputPath.c_str());
    cereal::BinaryInputArchive deArchive(input);
    deArchive(deInfo);
    return deInfo;
}


