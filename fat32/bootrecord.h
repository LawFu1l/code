//
// Created by Gun Hee Lee on 25. 5. 4.
//

#pragma once

#include "fat32_common.h"

class BootRecord
{
public:
    BootRecord() = default;

    explicit BootRecord(std::ifstream& ifs);

    auto sector_size() const -> long;
    auto cluster_size() const -> long;
    auto fat1_address() const -> long;
    auto data_area_address() const -> long;
    auto root_cluster_no() const -> uint32_t;
    auto fat_size() const -> long;


    auto to_s() -> std::string;

private:
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sector_count;
    uint8_t no_fats;
    uint32_t fat_size_32;
    uint32_t root_cluster;
};
