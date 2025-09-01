//
// Created by Gun Hee Lee on 25. 7. 27.
//
#include "string_util.h"
#include <string>
#include <utf8cpp/utf8.h>

namespace fat32::string::util
{
    using namespace std;

    auto rstrip(std::string_view sv) -> std::string
    {
        namespace rv = ranges;
        namespace vv = ranges::views;

        auto view = sv
            | vv::reverse
            | vv::drop_while([](const unsigned char c){ return isspace(c); })
            | vv::reverse;

        return {view.begin(), view.end()};
    }

    auto to_utf8(std::u16string const& name) -> std:: string
    {
        return utf8::utf16to8(name);
    }

}
