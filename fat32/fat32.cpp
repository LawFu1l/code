//
// Created by Gun Hee Lee on 25. 7. 24.
//

#include "fat32.h"

#include "bootrecord.h"
#include "node.h"
#include "fatarea.h"
#include "direntry.h"
#include "lfnentry.h"
#include "filesystem.h"
#include "fat32_common.h"
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

Fat32::Fat32(string filename)
    : m_filename{std::move(filename)}, m_stream{m_filename, ios::binary}
{
    m_br = make_unique<BootRecord>(m_stream);
    m_fat = make_unique<FatArea>(m_stream, m_br->fat1_address(), m_br->fat_size());
}

Fat32::~Fat32()
{
    destroy(m_root);
}

auto Fat32::build_filesystem() -> Filesystem
{
    m_root = make_root();
    expand_all(m_root);

    auto fs = Filesystem();
    if (!fs.unfold(m_root))
    {
        cout << "error build filesystem has failed" << endl;
        return Filesystem();
    }

    return fs;
}

auto Fat32::make_root() -> Node*
{
    auto stream = make_node_stream(m_br->root_cluster_no());
    return new Node("/"s,stream , NodeType::Dir, stream->size());
}

auto Fat32::get_extents_from(uint32_t cluster_no) const -> vector<Extent>
{
    const auto clusters =  m_fat->all_clusters_of(cluster_no);

    auto extents = vector<Extent>();
    auto c_size = m_br->cluster_size();
    auto data_addr = m_br->data_area_address();
    for (auto& c : clusters)
    {
        auto addr = data_addr + c_size * (c-2);
        extents.emplace_back(addr, c_size);
    }

    return extents;
}

auto Fat32::make_node_stream(const direntry& de) -> unique_ptr<Stream>
{
    return make_node_stream(de.start_cluster_no());
}

auto Fat32::make_node_stream(const uint32_t cluster_no) -> unique_ptr<Stream>
{
    return make_unique<Stream>(m_stream, get_extents_from(cluster_no));
}

auto Fat32::make_node(const direntry& de) -> Node*
{
    const auto type = de.is_dir() ? NodeType::Dir : NodeType::File;
    auto stream = make_node_stream(de);

    return new Node(de.name(), stream, type, de.file_size());
}

auto Fat32::read_lfn(core::io::byte_buffer& bb) const -> string
{
    bb.unget(0x20);
    vector<LfnEntry> lfns;

    while (bb.remained_size() >= 0x20)
    {
        LfnEntry lfn(bb);
        if (!lfn.is_valid())
            break;

        lfns.push_back(lfn);
    }

    bb.unget(0x20);

    ranges::reverse(lfns);
    const auto result = ranges::fold_left(lfns, ""s, [](const auto& acc, const auto& lfn) {
        return acc + lfn.get_name();
    });

    return fat32::string::util::rstrip(result);
}

auto Fat32::expand(Node* node) ->void
{
    if (!node->is_dir())
        return;

    auto bb = node->read_all();
    while (bb.has_remaining())
    {
        auto de = make_unique<direntry>(bb);

        if (de->is_empty()) break;
        if (de->is_volume()) continue;
        if (de->is_lfn())
        {
            auto name = read_lfn(bb);
            de = make_unique<direntry>(bb);
            de->set_name(name);
        }

        if (de->name() == "." || de->name() == "..") continue;

        const auto child = make_node(*de);
        child->set_path(node->get_path());
        node->add_child(child);
    }
}

auto Fat32::expand_all(Node* node) ->void
{
    if (!node->is_expandable())
        return;

    expand(node); // child를 만들어주는 과정이 된다.

    for (const auto c : node->children())
        if (c->is_expandable())
            expand_all(c);
}

auto Fat32::destroy(Node* node) ->void
{
    for (auto& c : node->children())
    {
        if (c->is_expandable())
            destroy(c);

        delete c;
    }
}
