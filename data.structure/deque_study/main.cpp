#include <iostream>
#include <deque>

using namespace std;

template <typename T>
void print_deque(const deque<T>& in)
{
    for (T e : in)
    {
        cout << e << endl;
    }
}

int main()
{
    deque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(1);

    print_deque<int>(dq);

    return 0;
}