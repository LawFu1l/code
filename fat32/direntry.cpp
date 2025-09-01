//
// Created by Gun Hee Lee on 25. 6. 29.
//

#include "direntry.h"

direntry::direntry(core::io::byte_buffer& bb)
{
    const auto coff = bb.offset();
    if (bb.is_zero(0x20))
    {
        _is_empty = true;
        return;
    }

    try
    {
        _is_deleted = bb.get_uint8() == 0xe5;

        bb.unget(1);
        auto name = fat32::string::util::rstrip( bb.get_ascii(8));
        auto ext = fat32::string::util::rstrip(bb.get_ascii(3));

        _name = ext.empty() ? name
                              : format("{}.{}", name, ext);

        const auto attr = bb.get_uint8();
        _is_vol  = attr == 0x08;
        _is_dir  = (attr & 0x10) == 0x10;
        _is_file = (attr & 0x20) == 0x20;
        _is_lfn  = (attr & 0x0f) == 0x0f;
        bb.skip(8); const auto hi = bb.get_uint16_le();
        bb.skip(4); const auto lo = bb.get_uint16_le();
        _cluster_no = hi << 16 | lo;
        _size = bb.get_uint32_le();
        // 비어있는 0x20인 경우를 찾는다.
    }
    catch (...)
    {}

    bb.offset(coff + 0x20);
}

auto direntry::get_type() const -> DentryType
{
    if (_is_dir) return DentryType::Dir;
    return DentryType::File;
}

auto direntry::to_s() const -> string
{
    return format("name: {}, start cluster: 0x{:X}, size: 0x{:X}",
        _name, _cluster_no, _size);
}