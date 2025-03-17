#include <iostream>

using namespace std;

/*
 *  컴파일 타임 최대공약수 구하기
 */

template <int A, int B>
struct GCD
{
    static const int result = GCD<B,A % B>::result;
};

template <int X>
struct GCD<X,0>
{
    static const int result = X;
};

int main()
{
    cout << "GCD 25, 5 : " << GCD<7484030, 522>::result << endl;
    return 0;
}
