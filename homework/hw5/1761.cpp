#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;

int n, m, tim, cnt;
vector<int> edge[MAXN], edgee[MAXN];
int dfn[MAXN], low[MAXN], col[MAXN];
vector<int> ans[MAXN];

void tarjan(int u, int las) {
    dfn[u] = low[u] = ++tim;
    for (int i = 0; i < edge[u].size(); i++) {
        int v = edge[u][i];
        bool flag = 1;
        if (v == las)
            continue;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                flag = 0;
        } else {
            low[u] = min(low[u], dfn[v]);
        }
        if (flag)
            edgee[u].push_back(v), edgee[v].push_back(u);
    }
}

void dfs(int u, int las) {
    ans[cnt].push_back(u);
    col[u] = cnt;
    for (int i = 0; i < edgee[u].size(); i++) {
        int v = edgee[u][i];
        if (v != las && !col[v])
            dfs(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i, 0);
    }
    for (int i = 1; i <= n; i++) {
        if (!col[i]) {
            cnt++;
            dfs(i, 0);
        }
    }
    cout << cnt << endl;
    for (int i = 1; i <= cnt; i++) {
        cout << ans[i].size() << " ";
        for (int j = 0; j < ans[i].size(); j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}