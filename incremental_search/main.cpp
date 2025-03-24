#include <iostream> 
#include <vector>
#include <cmath>
#include <numeric>
#include <cassert>
#include <stdnoreturn.h>

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
// 다항함수의 표현까지 일단 구현
struct Terms
{
    Terms(int degree, double coeff)
    {
        m_coeff = coeff;
        m_degree = degree;
    }
    int m_degree;
    double m_coeff;
}

class Polynomial
{
    public:
        explicit Polynomial(vector<double>& equation)
            : m_terms{equation}
        {
            m_degree = m_terms.size();
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

            m_terms.push_back(res);

            return res;
        }

        auto diff(vector<Terms>& input)
        {
            for (int i = 0; i < input.size(); i++)
            {
                Terms T = input[i];
                if (T.m_degree != 0)
                {
                    T.m_coeff = T.m_coeff * T.m_degree;
                    T.m_degree--;
                }
            }

            return input;
        }

        auto y_value(double x, vector<double>& input)
        {
            double result = 0;
            for (int i = 0; i < input.size(); i++)
            {
                result += input[i] * pow(x, i);
            }
            return result;
        }

        auto y_value(double x, vector<Terms>& input)
        {
            double result = 0;
            for (int i = 0; i < input.size(); i++)
            {
                Terms T = input[i];
                result = T.m_coeff * pow(x,T.m_degree);

            }
            return result;
        }
        auto y_value(enum Type type, double x)
        {
            double result = 0;
            switch (type)
            {
                case Type::Polynomial_diffed_once:
                    {
                        result =  y_value(x,m_terms[1]);
                    }
                case Type::Polynomial_diffed_twice:
                    {
                        result =  y_value(x,m_terms[2]);
                    }
                case Type::Polynomial:
                    {
                        result =  y_value(x,m_terms[0]);
                    }
                default:
                    break;
            }
            return result;
        }
        /*
           auto operator()(double x) -> double
           {
           double val = 0;
           for (int i = 0; i < m_degree; i++)
           val += pow(x, i) * m_terms[i];

           return val;
           }
           */
        // delta 값은 (to - from) / delta_size
        // 구분구적법 형식의 적분
        double integral(double from, double to, int delta_size, Type type = Type::Polynomial)
        {
            double delta = (to - from) / delta_size;
            double area = 0;
            while (from <= to)
            {
                area += ((y_value(type,from) + y_value(type,from+delta)) * delta) / 2;
                from += delta;
            }

            return area;
        }

        // y_value 함수 다시 구성 후 완성할 것
        // 수치해석 근 탐색 방법 중 하나를 정한 후, 함수 이름에 반영하여 알고리즘을 표현
        auto incremental_search(double x) ->double
        {
            double result;
            double delta = 0.00001;



            return result;
        }
        // 일계도함수 반환
        auto& differed_terms() const { return m_terms[1];}

        // 변곡점 존재여부 확인
        auto has_inflection_point() const { return m_terms[2].size() > 2;}

        // 극값의 존재여부 확인
        auto has_local_extreme_point() const { return m_terms[1].size() > 2;}

    private:
        vector<vector<double>> m_terms;
        int m_degree;
};

int main()
{
    // 오름차순으로 입력을 받아보자.
    // 1 + 2x + 3x^2
    vector coeff = {1., 2., 3.};
    Polynomial function(coeff);

    // 적분 결과
    auto area = function.integral(1, 2, 100000);
    cout << "area : " << area << endl;

    cout << "executed successfully" << endl;

    return 0;
}
