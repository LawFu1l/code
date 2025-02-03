#include <iostream>

using namespace std;

// 1 , 1, 2, 3, 5, 8

template<int X>
struct fibonacci
{
    static const int result = fibonacci<X - 1>::result + fibonacci<X - 2>::result;
};

template<>
struct fibonacci<0>
{
    static const int result = 1;
};

template<>
struct fibonacci<1>
{
    static const int result = 1;
};

int main()
{
    fibonacci<45> fib;
    cout <<" 계산 결과는 : " << fib.result << endl;

    return 0;
}