//
// Created by Gun Hee Lee on 25. 5. 4.
//

#pragma once

#include "fat32_common.h"

class FatArea
{
public:
    FatArea() = default;

    FatArea(std::ifstream& ifs, long start_addr, long size);

    [[nodiscard]]
    auto all_clusters_of(uint32_t cluster_no) const -> std::vector<uint32_t>;

    auto to_s() const -> std::string;

private:
    std::vector<uint32_t> _clusters;
};
