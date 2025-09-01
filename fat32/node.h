//
// Created by Gun Hee Lee on 25. 7. 21.
//

#pragma once

#include "fat32_common.h"
#include "stream.h"
#include <fstream>

using namespace std;

enum class NodeType
{
    Invalid,
    File,
    Dir,
    Softlink,
    Hardlink,
    Root
};

class Node
{
public:
    Node() = default;

    Node(string name, unique_ptr<Stream>& s, NodeType type, long actual_size);

    ~Node();

    auto set_path(const string& pwd) -> void;

    auto add_child(Node* child) -> void;

    auto is_file() const { return m_type == NodeType::File; }
    auto is_dir() const { return m_type == NodeType::Dir; }
    auto is_root() const { return m_name == "/"; }
    auto is_expandable() const -> bool;

    auto to_s() -> string;

    auto stream() const { return m_stream.get(); }

    auto read_all() const -> core::io::byte_buffer;

    auto export_to(const string& path) const -> bool;
    auto get_name() const { return m_name; }
    auto get_path() const { return m_path; }
    auto& children() const { return m_children; }

private:
    unique_ptr<Stream> m_stream;
    string m_name;
    string m_path;
    long m_actual_size{};
    long m_alloc_size{};
    NodeType m_type{NodeType::Invalid};
    vector<Node*> m_children;
};