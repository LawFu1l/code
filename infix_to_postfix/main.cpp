#include <iostream>
#include <stack>

using namespace std;

string to_postfix(const string& infix)
{
    string result  = "";
    stack<char> opers;

    for (char x : infix)
    {
        if (x == '(' || x == ' ') continue;
        else
        {
            // 피 연산자의 경우
            if (string("+-*/()").find(x) == string::npos)
            {
                result.push_back(x);
            }
            else
            {
                // 연산자의 경우
                if (x == '*' || x == '/' || x == '+' || x == '-')
                {
                    opers.push(x);
                }
                else if (x == ')')
                {
                    char op = opers.top();
                    opers.pop();
                    result.push_back(op);
                }
            }
        }
    }

    return result;
}

int main()
{
    string infix = "((111+5) * 3)";
    string postfix = to_postfix(infix);

    cout << postfix << endl;

    return 0;
}