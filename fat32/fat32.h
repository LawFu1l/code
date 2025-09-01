//
// Created by Gun Hee Lee on 25. 7. 24.
//

#pragma once

#include "bootrecord.h"
#include "fatarea.h"
#include "direntry.h"
#include "filesystem.h"
#include "extent.h"
#include "stream.h"
#include <string>
#include <fstream>

#include "node.h"

using namespace std;

class Node;

class Fat32
{
public:
    explicit Fat32(string filename);

    ~Fat32();

    auto build_filesystem() -> Filesystem;

private:
    auto make_root() -> Node*;

    auto get_extents_from(uint32_t cluster_no) const -> vector<Extent>;

    auto make_node_stream(const direntry& de) -> unique_ptr<Stream>;

    auto make_node_stream(uint32_t cluster_no) -> unique_ptr<Stream>;

    auto make_node(const direntry& de) -> Node*;

    auto read_lfn(core::io::byte_buffer& bb) const -> string;

    auto expand(Node* node) ->void;
    auto expand_all(Node* node) ->void;

    auto destroy(Node* node) ->void;
private:
    Node* m_root{};
    string m_filename;
    ifstream m_stream;
    unique_ptr<BootRecord> m_br;
    unique_ptr<FatArea> m_fat;
};
