//
// Created by Gun Hee Lee on 25. 7. 27.
//

#pragma once

#include <string_view>
#include <string>
#include <ranges>

namespace fat32::string::util
{
    auto rstrip(std::string_view sv) -> std::string;

    auto to_utf8(std::u16string const&) -> std:: string;
}
