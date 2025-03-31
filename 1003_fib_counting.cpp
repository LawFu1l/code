#include <iostream>
#include <vector>

using namespace std;

class Fibonacci
{
    public:
        Fibonacci(int n)
        {
            res = fib(n);
        }

        void print()
        {
            cout << this->res.first << " " << this->res.second << endl;
        }

    private:

        auto fib(int n) -> pair<int, int>
        {
            if (n == 0) return counts[0];
            if (n == 1) return counts[1];
            else
            {
                for (int i = 2; i <= n; i++)
                {
                    auto tmp = make_pair(counts[i-1].first + counts[i-2].first,
                            counts[i-1].second + counts[i-2].second);
                    counts.push_back(tmp);
                }
                return counts[n];
            }
        }

    private:
        // first -> 0 count     second-> 1 count
        vector<pair<int,int>> counts{make_pair(1,0), make_pair(0,1)};
        pair<int,int> res;
};

int main()
{
    int testcase; cin >> testcase;

    for (int i = 0; i < testcase; i++)
    {
        int n; cin >> n;
        Fibonacci res(n);
        res.print();
    }

    return 0;
}
