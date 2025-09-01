//
// Created by Gun Hee Lee on 25. 7. 26.
//

#pragma once

#include "fat32_common.h"

class LfnEntry final
{
public:
    explicit LfnEntry(core::io::byte_buffer& bb);

    LfnEntry() = default;

    [[nodiscard]]
    auto is_valid() const -> bool;

    [[nodiscard]]
    auto& get_name() const { return _name; }

private:
    std::string _name;
    uint8_t _order{};
    uint8_t _attr{};
};
