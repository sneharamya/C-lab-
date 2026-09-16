#include <iostream>
using namespace std;

inline int minVal(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

inline int minVal(int a, int b, int c)
{
    int min = a;

    if (b < min)
        min = b;

    if (c < min)
        min = c;

    return min;
}

int main()
{
    cout << "Smaller of 10 and 20 = " << minVal(10, 20) << endl;

    cout << "Smallest of 10, 5 and 15 = "
         << minVal(10, 5, 15) << endl;

    return 0;
}