#include <iostream>
#include <vector>

using namespace std;

auto binary_search_recursive(const vector<int> &in, int lo, int hi, int val) -> bool
{
    if (hi < lo)
        return false;

    const auto mid = lo + (hi - lo) / 2;
    if (in[mid] == val)
        return true;

    return in[mid] < val
        ? binary_search_recursive(in, mid+1,hi, val)
        : binary_search_recursive(in,lo, mid-1, val);
}

auto binary_search_iterative(const vector<int>& in, int target)
{
    int lo = 0, hi = in.size() -1;

    while (lo <= hi)
    {
        auto mid = lo + (hi - lo) / 2;
        if (in[mid] == target) return true;

        if (in[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;

        if (hi < lo) return false;
    }
}

int main()
{
    vector arr{1,2,3,4,5,6,7,8};

    for (int i=0; i<16; i++)
    {
        //bool res = binary_search_recursive(arr,0, arr.size() - 1, i);
        auto res = binary_search_iterative(arr, i);
        cout << i << " : " << res << endl;
    }


    return 0;
}