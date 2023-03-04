#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("1014.in", "w", stdout);
    time_t t;
    srand(time(&t));
    int n = 15;
    cout << n << endl;
    for (int i = 1; i <= n; i++)
        cout << rand() * rand()<< " ";
    cout << endl;
    for (int i = 1; i <= n; i++)
        cout << rand() * rand() << " ";
    return 0;
}