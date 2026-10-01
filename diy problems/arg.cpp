#include <iostream>
using namespace std;

int power(int base, int exp = 2)
{
    int result = 1;

    for (int i = 1; i <= exp; i++)
    {
        result = result * base;
    }

    return result;
}

int main()
{
    cout << "5^2 = " << power(5) << endl;
    cout << "2^10 = " << power(2, 10) << endl;

    return 0;
}