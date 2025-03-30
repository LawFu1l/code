#include <iostream>
#include <vector>

using namespace std;
auto init(int size)->vector<vector<char>>
{
    vector<vector<char>> result(size, vector<char>(size, '.'));
    return result;
}

auto draw(vector<vector<char>>& input) ->vector<vector<char>>
{
    int size = input.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (j == size / 2) input[i][j] = 'I';
            if (i == size / 2) input[i][j] = '+';
            if (j == size-i-1) input[i][j] = '*';
            if (j == size / 2 && i == size / 2) input[i][j] = 'O';

        }
    }
    return input;
}

void print_graph(auto& graph)
{
    int size = graph.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << graph[i][j];
        }
        cout << endl;
    }
}

int main()
{
    int testcase;
    cin >> testcase;
    for (int i = 0; i < testcase; i++)
    {
        int size;
        cin >> size;
        auto init_graph = init(size);
        auto graph = draw(init_graph);
        print_graph(graph);
    }
    return 0;
}