#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

int main()
{
    freopen("1665.in", "w", stdout);
    time_t t;
    srand(time(&t));
    int n = 20000, m = 10000, k = 3000;
    for (int i = 1; i <= k; i++)
    {
        cout << rand() % n + 1 << " " << rand() % n + 1 << endl;
    }
    return 0;
}