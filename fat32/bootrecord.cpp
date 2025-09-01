//
// Created by Gun Hee Lee on 25. 5. 4.
//

#include "bootrecord.h"
#include <sstream>
#include <fstream>

using namespace std;

BootRecord::BootRecord(ifstream& ifs)
{
    constexpr int SectorSize = 0x200;
    char buffer[SectorSize] = {};
    ifs.read(buffer,SectorSize);

    bytes_per_sector = *reinterpret_cast<short *>(buffer + 11); // invariant
    sectors_per_cluster = *reinterpret_cast<uint8_t *>(buffer + 13);
    reserved_sector_count = *reinterpret_cast<short *>(buffer + 14);
    no_fats = buffer[16];
    fat_size_32 = *reinterpret_cast<uint32_t *>(buffer + 36);
    root_cluster = *reinterpret_cast<uint32_t *>(buffer + 44);
}

auto BootRecord::sector_size() const -> long 
{ 
    return bytes_per_sector; 
}

auto BootRecord::cluster_size() const -> long 
{ 
    return bytes_per_sector * sectors_per_cluster; 
}

auto BootRecord::fat1_address() const -> long 
{ 
    return reserved_sector_count * bytes_per_sector; 
}

auto BootRecord::data_area_address() const -> long 
{ 
    return fat1_address() + (bytes_per_sector * fat_size_32) * 2; 
}

auto BootRecord::root_cluster_no() const -> uint32_t
{ 
    return root_cluster; 
}

auto BootRecord::fat_size() const -> long 
{ 
    return bytes_per_sector * fat_size_32; 
}


auto BootRecord::to_s() -> string
{
    stringstream result;
    result << format("cluster_size: 0x{:X}\n", cluster_size())
        << format("fat address : 0x{:X}\n", fat1_address())
        << format("fat size 32 : 0x{:X}\n", fat_size_32)
        << format("data area address : 0x{:X}\n", data_area_address());

    return result.str();
}

