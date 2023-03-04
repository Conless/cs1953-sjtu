// Statement and information
// Author: Conless
// Date: 2022-11-15
// File name: /course/22fall/sjtu/cs1953/homework/hw4/1746.cpp

#include <bits/stdc++.h>

#define LIM 0.0001

using namespace std;

const int MAXN = 2505;

int k, n, m;
int v[MAXN], s[MAXN], r[MAXN];
int siz[MAXN];
double f[MAXN][MAXN];
vector<int> son[MAXN];

void dfs(int u, double mid) {
    siz[u] = 1;
    if (u)
        f[u][1] = (double)s[u] - mid * v[u];
    else
        f[u][0] = 0;
    for (int i = 0; i < son[u].size(); i++) {
        int v = son[u][i];
        dfs(v, mid);
        siz[u] += siz[v];
        int tt = 1;
        if (!u)
            tt = 0;
        for (int j = siz[u]; j >= tt; j--)
            for (int l = 0; l <= siz[v]; l++) {
                if (f[u][j] >= 0 && f[v][l] >= 0)
                    f[u][j + l] = max(f[u][j + l], f[u][j] + f[v][l]);
            }
    }
    return;
}

int main() {
    // freopen("1746.in", "r", stdin);
    scanf("%d%d", &k, &n);
    int mxv = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &v[i], &s[i], &r[i]);
        son[r[i]].push_back(i);
        mxv = max(mxv, s[i]);
    }
    double l = 0.0, r = mxv, ans = 0.0;
    while (r - l >= LIM) {
        double mid = (l + r) / 2.0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n + 1; j++)
                f[i][j] = -LIM;
        dfs(0, mid);
        if (f[0][k + 1] > LIM) {
            ans = mid;
            l = mid + LIM;
        } else
            r = mid - LIM;
    }
    printf("%.3lf\n", ans);
    return 0;
}