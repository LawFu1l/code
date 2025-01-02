//
// Created by USER on 24. 12. 27.
//

#pragma once

#include <string>

using std::string;

namespace MyExcel {
    class Cell;

    template<typename T>
    struct Node
    {
        Node* prev;
        T s;
        Node(Node* pre, const T& s) : prev(pre), s{s} {}
    };

    class Vector
    {
    public:
        explicit Vector(int n = 1);
        ~Vector();

        void push_back(const string& s);

        string operator[](int i) const;

        void remove(int n);

        int size() const;
    private:
        string* data;
        int capacity;
        int length;
    };

    class Stack
    {
    public:
        Stack();
        ~Stack();

        void push(string s);
        string pop();
        string const peek();
        bool is_empty();

    private:
        Node<string>* current;
        Node<string> start;
    };

    class NumStack
    {
    public:
        NumStack();
        ~NumStack();

        void push(double s);
        double pop();
        double peek();
        bool is_empty();

    private:
        Node<double>* current;
        Node<double> start;
    };

    class Table
    {
    public:
        Table(int max_row_size, int max_col_size);

        virtual ~Table();

        // 새로운 셀을 다음 row,col에 해당하는 칸에 집어넣음
        void reg_cell(Cell* c, int row, int col);

        int to_numeric(const string& s);

        int to_numeric(int row, int col);

        string stringify(const string& s);
        string stringify(int row, int col);

        virtual string print_table() = 0;

    protected:
        int max_row_size, max_col_size;

        Cell*** data_table;
    };

    class Cell
    {
    public:
        virtual ~Cell() = default;

        Cell(string data, int x, int y, Table* table);
        virtual string stringify();
        virtual int to_numeric();

    protected:
        int x, y;
        Table* table;
        string data;
    };

    class TxtTable : public Table
    {
    public:
        TxtTable(int row, int col);

        string print_table() override;

    private:
        string repeat_char(int n , char c);

        static string col_num_to_str(int n);
    };

    std::ostream& operator<<(std::ostream& o, Table& table);

}
