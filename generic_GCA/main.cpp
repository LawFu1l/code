#include <iostream>

using namespace std;

/*
 *  컴파일 타임 팩토리얼 계산
 *  프로그래밍에서의 과정 : 전처리 -> 컴파일 -> 어셈 -> 링킹 -> 로드 ->
 *  컴파일 타임 : 전처리부터 어셈블 단계까지
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
