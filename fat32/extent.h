//
// Created by Gun Hee Lee on 25. 7. 20.
//

#pragma once

struct Extent
{
    Extent(const long start, const int size)
        : m_start{start}, m_size{size} {}

    [[nodiscard]]
    auto contains(const long pos) const -> bool
    {
        return pos >= m_start and pos < m_start + m_size;
    }

    long m_start;
    int m_size;
};
