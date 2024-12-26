#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef vector<double> P;

P position_p1(double x, double y)
{
    vector<double> p1;
    p1.push_back(x);
    p1.push_back(y);

    return p1;
}

P position_p2(double x, double y)
{
    vector<double> p2;
    p2.push_back(x);
    p2.push_back(y);

    return p2;
}

double range_calculator(const P& p1,const P& p2)
{
    double xrange = p1[0] - p2[0];
    double yrange = p1[1] - p2[1];
    double x_range_sqr =pow(xrange,2);
    double y_range_sqr = pow(yrange,2);
    double sum = x_range_sqr + y_range_sqr;
    double distance = sqrt(sum);

    return distance;
}

int main()
{
    double result = range_calculator(position_p1(1,4),position_p2(1,5));

    printf("%lf",result);
    return 0;
}
