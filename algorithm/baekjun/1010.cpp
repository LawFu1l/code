#include <iostream>

using namespace std;

long possible_site(int west_site, int east_site)
{
    if (west_site > east_site)
        return 1;

    auto result = 1L;
    for (int r=1; west_site > 0; west_site--, east_site--, r++)
    {
        result *= east_site;
        result /= r;
    }

    return result;
}


int main()
{
    int test_site;
    cin >> test_site;

    for (int i=0; i<test_site; i++)
    {
        int west_site, east_site;
        cin >> west_site >> east_site;

        cout << possible_site(west_site, east_site) << endl;
    }

    return 0;
}
