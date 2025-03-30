#include <iostream>
#include <vector>

using namespace std;

int calculate(vector<int>& input)
{
    int result = 1;
    for (auto& e : input)
        result = (result * e) % 10;
    return result;
}
vector<int> get_data()
{
    int size;
    cin >> size;
    vector<int> result;
    for (int i = 0; i <size; i++)
    {
        int input;
        cin >> input;
        input = input % 10;
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
        vector<int> test = get_data();
        int calculated = calculate(test);

        cout << calculated << endl;
    }

    return 0;
}