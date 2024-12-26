#include <iostream>
#include <vector>

using namespace std;

/*
 *  입력 자료의 오름차순 정리
 * 최대 값 담는 변수 선언 후 값은 입력의 0번째 첨자값으로 초기화, for 루프를 활용하며 매 회차 갱신
 */
vector<double> sort(const vector<double>& input)
{
    vector<double> result = input;
    const int size = input.size();

    for (int i = 0; i <size;i++)
    {
        for (int j = i; j < size; j++)
        {
            if (result[i] > result[j])
            {
                double tmp = result[j];
                result[j] = result[i];
                result[i] = tmp;
            }
        }
    }

    return result;
}

void print_arr(const vector<double>& result)
{
    for (double i : result)
    {
        cout << i << " ";
    }
}

int main()
{
    //8개 첨자범위 0~7
    auto input = vector<double>{1, 0, 2.2, 1, 0, 9, 55, 22};
    auto result = sort(input);
    print_arr(result);

    return 0;
}
