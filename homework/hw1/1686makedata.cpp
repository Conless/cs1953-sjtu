#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("1686.in", "w", stdout);
    time_t t;
    int n = 1000000, m = 0;
    srand(time(&t));
    cout << n << " " << m << endl;
    for (int i = 1; i <= n; i++)
        cout << rand()%2;
    return 0;
}