// Statement and information
// Author: Conless
// Date: 2022-11-16
// File name: /course/22fall/sjtu/cs1953/homework/hw4/1746.cpp

#include <bits/stdc++.h>

#define LIM 0.00001

using namespace std;

const int MAXN = 2505;

int n, k, tim;
int v[MAXN], s[MAXN], r[MAXN];
double d[MAXN], f[MAXN][MAXN];
int dfn[MAXN], las[MAXN];
vector<int> son[MAXN];

void dfs(int u) {
    dfn[u] = tim++;
    for (auto v : son[u])
        dfs(v);
    las[dfn[u]] = tim;
}

bool check(double mid) {
    for (int i = 1; i <= n; i++)
        d[dfn[i]] = (double)s[i] - mid * v[i];
    for (int i = 1; i <= n + 1; i++)
        for (int j = 0; j <= k + 1; j++)
            f[i][j] = -10000000.0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= min(i, k + 1); j++) {
            f[i + 1][j + 1] = max(f[i + 1][j + 1], f[i][j] + d[i]);
            f[las[i]][j] = max(f[las[i]][j], f[i][j]);
        }
    return f[n + 1][k + 1] >= LIM;
}

int main() {
    // freopen("1746.in", "r", stdin);
    scanf("%d%d", &k, &n);
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &v[i], &s[i], &r[i]);
        son[r[i]].push_back(i);
        mx = max(mx, s[i]);
    }
    dfs(0);
    double l = 0.0, r = 10000000.0, ans = 0.0;
    while (r - l >= LIM) {
        double mid = (l + r) / 2.0;
        if (check(mid)) {
            ans = mid;
            l = mid + LIM;
        } else
            r = mid - LIM;
    }
    printf("%.3lf\n", ans);
    return 0;
}