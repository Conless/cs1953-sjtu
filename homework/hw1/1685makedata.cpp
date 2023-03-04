#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("1685.in", "w", stdout);
    time_t t;
    srand(time(&t));
    int n = 5e4, q = 2e4;
    cout << n << " " << q << endl;
    for (int i = 1; i <= n; i++)
        cout << rand() % 100 + 1 << " ";
    cout << endl;
    for (int i = 1; i <= q; i++)
    {
        int l = rand() % (q - 100) + 1;
        int r = l + rand() % 50 + 1;
        cout << l << " " << r << endl;
    }
    return 0;
}