#include <bits/stdc++.h>

using namespace std;

int main()
{
    time_t ti;
    srand(time(&ti));
    freopen("1706.in", "w", stdout);
    int n = 2e4, m = 5e5, s = 1, t = n, g = 1e6, q = 1;
    printf("%d %d %d %d %d %d\n", n, m, s, t, g, q);
    for (int i = 1; i <= n; i++)
    {
        int h = rand() % 1000 + 1, l = h + 10000 + rand() % 10000;
        printf("%d %d\n", h, l);
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        u = rand() % n + 1, v = rand() % n + 1;
        while (v == u)
            v = rand() % n + 1;
        w = rand() % 100000 + 1;
        printf("%d %d %d\n", u, v, w);
    }
    return 0;
}