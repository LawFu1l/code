#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
 * 증분법을 구현하기 위한 과정으로 다음과 같은 구현 순서를 가진다.
 * 1. 다항함수의 수식적 표현과 기능
 *      - 실수의 연속성을 만족하기 위해 실수 전체 범위에서 정의되도록 한다.
 *      - 다항함수는 오름차순 정리의 입력을 받도록 한다.
 *
 * 2. 증분적 표현 구현과 변화량 단위 구현
 *      - 변화량 단위는 사용자 정의와 기본 옵션을 두도록 하자.
 * 3. 필요하다면, 배열에 들어가는 값도 구조체로 선언해보자
 * 사용의 예시
 * [3,5,2] -> 3x^2 + 5x + 2
 */

enum class Type
{
    Polynomial,
    Exponential,
    Logarithmic,
    Trigonometric
};

struct Entry
{
    Entry() {}
};

class Polynomial
{
public:
    explicit Polynomial(vector<double>& equation)
        : m_terms{equation}
    {
        m_degree = m_terms.size();
        vector<double> derivated = diff(equation);
        vector<double> twice_derivated = diff(derivated);
    }

    //
    auto y_value(double __x)->int
    {
        double val = 0;
        for (int i = 0; i < m_degree; i++)
            val += pow(__x,i) * m_terms[i];

        return val;
    }

    // 3 2 1
    // 미분한는 함수
    auto diff(vector<double>& input) ->vector<double>
    {
        vector<double> res;
        int size = input.size();
        for (int i = 1; i < size; i++)
        {
            double diffed = i * input[i];

            res.push_back(diffed);
        }
        differed_terms.push_back(res);

        return res;
    }

    // delta 값은 (to - from) / delta_size
    // 구분구적법 형식의 적분
    double integral(double from, double to, int delta_size)
    {
        double delta = (to-from) / delta_size;
        double area = 0;
        while (from <= to)
        {
            area += delta * (y_value(from) + y_value(from + delta)) / 2;
            from += delta;
        }

        return area;
    }

    // 변곡점 존재여부 확인
    auto check_inflection(){ return differed_terms[1].size() > 2;}

    // 극값의 존재여부 확인
    auto check_local_extreme(){ return differed_terms[0].size() > 2;}

    //변곡점 x위치 확인
    auto position_inflection()
    {
        double res;

        return res;
    }

    // 극값 관찰, 극값을 가지는 x 반환
    auto position_local_extreme()
    {
        double res;

        return res;
    }

    vector<double> m_terms;
    vector<vector<double>> differed_terms;
    int m_degree;
    int differed = 0;
};

int main()
{
    // 오름차순으로 입력을 받아보자.
    // 1+2x + 3x^2
    vector<double> xs = {1,2,3};
    int x_val = 3;
    Polynomial function(xs);
    int y = function.y_value(x_val);
    // 적분 결과는
    double area = function.integral(1,2,100000);
    cout << "area : " << area << endl;
    for (auto& i : function.differed_terms)
    {
        for (auto& e : i)
        {
            cout << " " << e << " ";
        }
        cout << "\n";
    }
    cout << "executed successfully" << endl;

    cout << "function val : " << y ;

    return 0;
}
