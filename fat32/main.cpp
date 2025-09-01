#include "fat32.h"
#include "node.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    auto path = "/Users/gunhee/Desktop/FAT32_simple.mdf"s;
    auto ifs = ifstream(path, ios::binary);

    auto fat32 = Fat32(path);

    auto fs = fat32.build_filesystem();

    auto node = fs["/DIR1/PORT.JPG"];
    cout << node->to_s() << endl;
    node->export_to("/Users/gunhee/Desktop/port.jpg");

    return 0;
}
