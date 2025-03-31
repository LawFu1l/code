#include <iostream>

using namespace std;

auto get_input()->pair<int,int>
{
    int base, exponent;
    cin >> base >> exponent;
    return  make_pair(base,exponent);
}

auto computer_number(pair<int,int>& input)
{
    // 곱하기의 항등원은 1
    auto result = 1;
    for (int i = 0; i < input.second; i++)
        result = (result * input.first) % 10;

    return result == 0 ? 10 : result;
}

int main()
{
    int testcase; cin >> testcase;
    for (int i = 0; i < testcase; i++)
    {
        auto input = get_input();
        auto result = computer_number(input);
        cout << result << endl;
    }
    return 0;
}
