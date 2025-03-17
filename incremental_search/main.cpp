#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cassert>

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
 *
 * 3월 17일 해야 할 것 : y_value 함수 재구성, incremental_search 함수 완성하기
 */

enum class Type
{
    Polynomial,
    Polynomial_diffed_once,
    Polynomial_diffed_twice,
    Exponential,
    Logarithmic,
    Trigonometric
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

    // 3 2 1
    // 미분하는 함수
    // 다항함수 한정
    auto diff(vector<double>& input) -> vector<double>
    {
        vector<double> res;

        for (int i = 1; i < input.size(); i++)
        {
            double diffed = i * input[i];

            res.push_back(diffed);
        }

        m_differed_terms.push_back(res);

        return res;
    }

    auto y_value(enum Type type, double x)
    {
        switch (type)
        {
            case Type::Polynomial_diffed_once:
            {
                break;
            }
            case Type::Polynomial_diffed_twice:
            {
                break;
            }

        }

    }

    auto operator()(double x) -> double
    {
        double val = 0;
        for (int i = 0; i < m_degree; i++)
            val += pow(x, i) * m_terms[i];

        return val;
    }

    // delta 값은 (to - from) / delta_size
    // 구분구적법 형식의 적분
    double integral(double from, double to, int delta_size)
    {
        double delta = (to - from) / delta_size;
        double area = 0;
        while (from <= to)
        {
            area += delta * ((*this)(from) + (*this)(from + delta)) / 2.0;
            from += delta;
        }

        return area;
    }

    // y_value 함수 다시 구성 후 완성할 것
    auto incremental_search(double x) ->double
    {
        double result;
        double delta = 0.00001;
        


        return result;
    }

    auto& differed_terms() const { return m_differed_terms;  }

    // 변곡점 존재여부 확인
    auto has_inflection_point() const { return m_differed_terms[1].size() > 2; }

    // 극값의 존재여부 확인
    auto has_local_extreme_point() const { return m_differed_terms[0].size() > 2; }

private:
    vector<double> m_terms;
    vector<vector<double>> m_differed_terms;
    int m_degree;
    int differed = 0;
};

int main()
{
    // 오름차순으로 입력을 받아보자.
    // 1 + 2x + 3x^2
    vector coeff = {1., 2., 3.};
    Polynomial function(coeff);

    assert(function(3) == 34);

    // 적분 결과
    auto area = function.integral(1, 2, 100000);
    cout << "area : " << area << endl;

    for (auto& i : function.differed_terms())
    {
        for (auto& e : i)
            cout << " " << e << " ";
        
        cout << "\n";
    }

    cout << "executed successfully" << endl;

    return 0;
}
