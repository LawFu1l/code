//
// Created by Gun Hee Lee on 25. 7. 20.
//

#pragma once

#include "extent.h"
#include "fat32_common.h"
#include <istream>


using namespace std;

class Stream
{
public:
    Stream(istream& input, vector<Extent> extents);

    // TODO
    // 1. m_offset을 포함하는 extent 찾기
    // 2. 최종으로는 m_offset은 읽은 개수만큼 더해져 있어야 한다.

    auto seek(long offset, ios::seekdir dir) -> Stream&;

    auto read(char* buf, streamsize count) -> int;

    [[nodiscard]]
    auto size() const -> streamsize;

private:
    istream& m_ss;
    vector<Extent> m_extents;
    long m_offset;
};