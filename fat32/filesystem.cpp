//
// Created by Gun Hee Lee on 25. 7. 27.
//

#include "filesystem.h"
#include "node.h"
#include <iostream>

Filesystem::Filesystem(string name) : m_name{std::move(name)}
{
}

auto Filesystem::unfold(Node* node) -> bool
{
    cout << node->to_s() << endl;

    //m_map[node->get_path()] = node;
    auto [it, s0] = m_map.insert({node->get_path(),node});

    for (auto& child : node->children())
    {
        cout << child->to_s() << endl;
        auto [_,s1] = m_map.insert({child->get_path(), child});

        m_map[child->get_path()] = child;

        if (child->is_expandable())
            unfold(child);
    }

    return true;
}

auto Filesystem::operator[](const string& index) -> Node*
{
    return m_map[index];
}
