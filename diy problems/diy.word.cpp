#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    string s;
    string word;

    cout << "Enter a sentence: ";
    getline(cin, s);

    stringstream ss(s);

    string words[100];
    int n = 0;

    while (ss >> word)
    {
        words[n] = word;
        n++;
    }

    cout << "Reversed sentence: ";

    for (int i = n - 1; i >= 0; i--)
    {
        cout << words[i];

        if (i != 0)
            cout << " ";
    }

    cout << endl;

    return 0;
}