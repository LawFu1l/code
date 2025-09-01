
#include "fatarea.h"

#include <fstream>
#include <sstream>
#include <ios>

FatArea::FatArea(std::ifstream& ifs, long start_addr, long size)
{
    ifs.seekg(start_addr, std::ios::beg);
    auto fat1 = std::vector<uint8_t>(size);
    ifs.read(reinterpret_cast<char*>(&fat1[0]), size);
    int cluster_count = fat1.size() / 4;

    auto bb = core::io::byte_buffer(&fat1[0], fat1.size());

    for (int i = 0; i < cluster_count; ++i)
        _clusters.push_back(bb.get_uint32_le());
}

auto FatArea::all_clusters_of(uint32_t cluster_no) const -> std::vector<uint32_t>
{
    auto result = std::vector<uint32_t>();
    uint32_t next_no = cluster_no;

    do
    {
        result.push_back(next_no);
        next_no = _clusters[next_no];
    }
    while (next_no != 0xfffffff && next_no != 0xffffff8);

    return result;
}

auto FatArea::to_s() const -> std::string
{
    std::stringstream ss;
    for (int i = 0; i < 9; ++i)
        ss << std::hex << _clusters[i] << " ";

    return ss.str();
}
