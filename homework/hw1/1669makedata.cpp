#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("1669.in", "w", stdout);
    time_t t;
    srand(time(&t));
    int n = 500, m = 200;
    cout << n << " " << m << endl;
    for (int i = 1; i < n; i++)
        cout << rand() % 100 << " ";
    return 0;
}