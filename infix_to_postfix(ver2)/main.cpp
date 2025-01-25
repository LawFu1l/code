#include <iostream>
#include <string>
#include <stack>
#include <vector>

/*
 *  이번 구현의 목표
 *  #1 : 실제 계산 기능 추가
 *  #2 : 두 자리 이상의 수 계산 지원
 */
using namespace std;


double calculate(const string& postfix)
{
    double result = 0;
    int size = postfix.size();
    vector<double> values;

    for (int i = 0; i < size; )
    {
        // postfix[i] 가 숫자인 경우
        if (string("1234567890").find(postfix[i]) != string::npos)
        {
            auto val = ""s;
            val.push_back(postfix[i]);
            ++i;

            while (string("1234567890").find(postfix[i]) != string::npos)
            {
                val.push_back(postfix[i]);
                ++i;
            }
            //val이 완성되고 인덱스는 옮겨진다.
            values.push_back(stoi(val));
        }
        else if (postfix[i] == ' ')
        {
            ++i;
            continue;
        }
        else
        {
            double calculated = 0;
            // 연산자를 식별하여 피연산자들의 계산을 완성한다.
            if (postfix[i] == '+')
            {
                calculated = values[0] + values[1];
                values.clear();
                values.push_back(calculated);
                ++i;
                continue;
            }
            if (postfix[i] == '-')
            {
                calculated = values[0] - values[1];
                values.clear();
                values.push_back(calculated);
                ++i;
                continue;
            }
            if (postfix[i] == '*')
            {
                calculated = values[0] * values[1];
                values.clear();
                values.push_back(calculated);
                ++i;
                continue;
            }
            if (postfix[i] == '/')
            {
                calculated = values[0] / values[1];
                values.clear();
                values.push_back(calculated);
                ++i;
            }
        }
    }
    result = values[0];

    return result;
}

// 두 자리 이상의 식 표현 가능
string to_postfix(const string& infix)
{
    string result = "";
    int size = infix.size();
    stack<char> opers;

    for (int i = 0; i < size;)
    {
        if (infix[i] == '(' || infix[i] == ' ')
        {
            i++;
            continue;
        }
        else
        {
            // 피 연산자의 경우
            if (string("+-*/()").find(infix[i]) == string::npos)
            {
                result.push_back(infix[i]);
                ++i;

                if (string("+-*/()").find(infix[i]) == string::npos)
                {
                    while (string("+-*/() ").find(infix[i]) == string::npos)
                    {
                        result.push_back(infix[i]);
                        ++i;
                    }
                    result.push_back(' ');
                }
            }
            else
            {
                // 연산자의 경우
                if (infix[i] == '*' || infix[i] == '/' || infix[i] == '+' || infix[i] == '-')
                {
                    opers.push(infix[i]);
                    ++i;
                }
                else if (infix[i] == ')')
                {
                    char op = opers.top();
                    opers.pop();
                    result.push_back(op);
                    ++i;
                }
            }
        }
    }
    return result;
}

int main()
{
    auto expresstion = "((22 + 42) * 71)"s;
    auto transed_expr = to_postfix(expresstion);
    // 22 42+ 71*

    double result = calculate(transed_expr);
    cout << transed_expr << endl;
    cout << result << endl;
    
    return 0;
}