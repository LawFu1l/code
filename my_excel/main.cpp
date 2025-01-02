#include <iostream>
#include <string>
#include <fstream>

#include "my_excel.util.h"

using namespace std;

int main()
{
    MyExcel::TxtTable table(5,5);

    ofstream out("test.txt");

    table.reg_cell(new MyExcel::Cell("Hello",0 ,0, &table), 0, 0);
    table.reg_cell(new MyExcel::Cell("c++",0 ,1, &table), 0, 1);
    table.reg_cell(new MyExcel::Cell("programming",1 ,1, &table), 1, 1);


    cout << endl << table;
    out << table;

    return 0;
}