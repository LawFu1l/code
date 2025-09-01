//
// Created by Gun Hee Lee on 25. 6. 29.
//
#pragma once

#include "fat32_common.h"

class FatArea;
using namespace std;

enum class DentryType
{
    File,
    Dir,
    Softlink,
    Hardlink
};

class direntry
{
public:

    explicit direntry(core::io::byte_buffer& bb);

    auto get_type() const -> DentryType;

    auto start_cluster_no() const{ return _cluster_no; }

    [[nodiscard]] auto is_dir() const { return _is_dir; }
    [[nodiscard]] auto is_file() const { return _is_file; }
    [[nodiscard]] auto is_lfn() const { return _is_lfn; }
    [[nodiscard]] auto file_size() const { return _size; }

    [[nodiscard]]
    auto to_s() const -> string;

    auto is_empty() const { return _is_empty; }
    auto is_volume() const { return _is_vol; }

    auto set_name(const string& name) { _name = name; }
    auto& name() const { return _name; }

private:
    string _lfn_name;
    bool _is_lfn;
    bool _is_vol;
    bool _is_deleted;
    bool _is_dir;
    bool _is_file;
    bool _is_empty;
    uint32_t _size;
    string _name;
    uint32_t _cluster_no{};
};