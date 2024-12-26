#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> init_matrix(int size)
{
    vector<vector<int>> init_result;


    for (int i = 0; i < size;i++)
    {
        vector<int> init_arr;
        for(int j = 0 ; j < size; j++)
        {
            init_arr.push_back(0);
        }
        init_result.push_back(init_arr);
    }
    return init_result;
}

vector<int> make_moving_order(int size)
{
    vector<int> res;
    int loop_num_Max = (size-1) / 2;
    int loop_start = 1;

    for (int i = 1; i <= loop_num_Max; i++)
    {
        for (int j = 0; j < 8 * loop_start; j++)
        {
            if (j == 0) res.push_back(3);
            if (0 < j && j < 2 * loop_start) res.push_back(1);
            if (2 * loop_start <= j && j < 4 * loop_start) res.push_back(2);
            if (4 * loop_start <= j && j < 6 * loop_start) res.push_back(0);
            if (6* loop_start <= j && j < 8 * loop_start) res.push_back(3);
        }
        loop_start++;
    }

    return res;
}

vector<vector<int>> make_array(const vector<int>& moving_order, vector<vector<int>> result ,int size)
{
    int total_orders = moving_order.size();
    int row= size / 2;
    int col = size / 2;

    result[col][row] = 1;

    for (int i = 0; i < total_orders;i++)
    {
        // 0,1,2,3 각각 상,하,좌,우
        switch (moving_order[i]) {
            case 0:
                col--;
                break;
            case 1:
                col++;
                break;
            case 2:
                row --;
                break;
            case 3:
                row++;
                break;
        }
        result[col][row] = i + 2;
    }
    return result;
}

void printArr(const vector<vector<int>>& result)
{
    int arr_size = result.size();
    for (int i = 0; i < arr_size; i++)
    {
        for(int j = 0; j < arr_size; j++)
        {
            cout  << " " << result[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int mainloop = 7;

    for (int i = 1 ; i <= mainloop; i = i + 2)
    {
        vector<vector<int>> result = init_matrix(i) ;
        vector<int> moving_order = make_moving_order(i);
        result = make_array(moving_order,result,i);
        printArr(result);

        cout << endl;
    }

    return 0;
}
