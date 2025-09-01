//
// Created by Gun Hee Lee on 25. 7. 26.
//

#include "lfnentry.h"

LfnEntry::LfnEntry(core::io::byte_buffer& bb)
{
    _order = bb.get_uint8();
    const auto name1 = bb.get_raw_unicode16_le(5);
    _attr = bb.get_uint8();

    bb.skip(2);

    const auto name2 = bb.get_raw_unicode16_le(6);
    bb.skip(2);
    const auto name3 = bb.get_raw_unicode16_le(2);

    auto name = name1 + name2 + name3;

    // 널 종료까지 자르기
    if (const auto end_pos = name.find(u'\0'); end_pos != std::u16string::npos)
        name.resize(end_pos);

    _name = fat32::string::util::to_utf8(name);
}

auto LfnEntry::is_valid() const -> bool
{
    const std::string ics = "/\\:*?<>";
    if (_attr == 0x0f && _order <= 0x54)
    {
        for (auto const c: ics)
            if (_name.contains(c)) return false;

        return true;
    }

    return false;
}