#include <iostream>
#include <vector>

using namespace std;

int digit_of_one(const vector<int>& input)
{
    int result = 1;
    for (auto& e : input)
    {
        auto small = e % 10;
        result = (result * small) % 10;
    }

    return result;
}

auto get_data() -> vector<int> 
{
    int size; cin >> size;
    vector<int> result;
    for (int i = 0; i < size; i++)
    {
        int input; cin >> input;
        result.push_back(input);
    }

    return result;
}

int main()
{
    int testcase;
    cin >> testcase;
    for (int i = 0; i < testcase; i++)
    {
        auto data = get_data();
        int digit = digit_of_one(data);

        cout << digit << endl;
    }

    return 0;
}