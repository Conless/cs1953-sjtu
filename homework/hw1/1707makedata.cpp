#include <bits/stdc++.h>

using namespace std;

int main()
{
    time_t t;
    srand(time(&t));
    freopen("1707.in", "w", stdout);
    int n = 20, m = 4;
    cout << n << " " << m << endl;
    for (int i = 1; i <= n; i++)
        cout << rand() % 100 + 1 << " ";
    return 0;
}