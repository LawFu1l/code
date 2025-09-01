//
// Created by Gun Hee Lee on 25. 7. 27.
//

#pragma once
#include <map>
#include <string>

class Node;

class Filesystem
{
public:
    explicit Filesystem(std::string name);
    Filesystem() = default;

    auto operator[](const std::string& index) -> Node*;
    auto unfold(Node* node) -> bool;

private:
    std::string m_name{};
    std::map<std::string,Node*> m_map;
};
