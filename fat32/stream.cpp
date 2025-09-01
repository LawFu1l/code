#include "stream.h"

using namespace std;

Stream::Stream(istream& input, vector<Extent> extents)
    : m_ss(input), m_extents(std::move(extents)), m_offset(0)
{}

// TODO
// 1. m_offset을 포함하는 extent 찾기
// 2. 최종으로는 m_offset은 읽은 개수만큼 더해져 있어야 한다.
auto Stream::seek(const long offset, const ios::seekdir dir) -> Stream&
{
    switch (dir)
    {
        case ios::beg: m_offset = offset; break;
        case ios::end:
        case ios::cur: m_offset += offset; break;
        default:
            throw logic_error("wrong dir");
    }

    return *this;
}

auto Stream::read(char* buf, const streamsize count) -> int
{
    int total_read = 0;
    // extent의 논리적 끝(반복문의 회차마다 증가)
    int upto = 0;
    auto remained = count;
    for (const auto& e : m_extents)
    {
        upto += e.m_size;
        if (upto <= m_offset)
            continue;

        const auto lo = e.m_size - (upto - m_offset);
        const auto ro = e.m_start + lo;

        m_ss.seekg(ro,ios::beg);
        const auto to_read = remained < e.m_size - lo ? remained : e.m_size - lo;
        m_ss.read(buf + total_read, to_read);
        const auto rd = m_ss.gcount();
        total_read += static_cast<int>(rd);
        remained -= rd;
        m_offset += rd;

        if (rd <= 0 || total_read == count)
            break;
    }

    return total_read;
}

auto Stream::size() const -> streamsize
{
    streamsize res = 0;
    for (const auto&e : m_extents)
        res += e.m_size;

    return res;
}