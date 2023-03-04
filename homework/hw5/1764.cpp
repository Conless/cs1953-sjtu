#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXM = 1e6 + 5;

struct Edge {
    int u, v, next;
} edge[MAXM << 1];

int n, m, cnt;
int head[MAXN];

void add_edge(int u, int v) {
    cnt++;
    edge[cnt] = {u, v, head[u]};
    head[u] = cnt;
}

int tim, tot;
int dfn[MAXN], low[MAXN], ins[MAXN], col[MAXN], siz[MAXN];
stack<int> st;

vector<int> ed[MAXN];
unordered_map<int, int> inss[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    ins[u] = 1;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        tot++;
        int tp;
        do {
            tp = st.top();
            ins[tp] = 0;
            col[tp] = tot;
            siz[tot]++;
            st.pop();
        } while (tp != u);
    }
}

int vis[MAXN], d[MAXN];
long long x, f[MAXN];
int ans1, ans2;

void dfs(int u) {
    vis[u] = 1;
    f[u] = 1;
    d[u] = 0;
    for (auto v : ed[u]) {
        if (!vis[v])
            dfs(v);
        if (d[v] > d[u]) {
            d[u] = d[v];
            f[u] = f[v];
        } else if (d[v] == d[u]) {
            f[u] = (f[u] + f[v]) % x;
        }
    }
    d[u] += siz[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> x;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i);
    }
    for (int i = 1; i <= m; i++) {
        int cu = col[edge[i].u], cv = col[edge[i].v];
        if (cu != cv && inss[cu].find(cv) == inss[cu].end()) {
            inss[cu].insert({cv, 1});
            ed[cu].push_back(cv);
        }
    }
    for (int i = tot; i >= 1; i--) {
        if (!vis[i]) {
            dfs(i);
            if (d[i] > ans1) {
                ans1 = d[i];
                ans2 = f[i];
            } else if (d[i] == ans1) {
                ans2 = (ans2 + f[i]) % x;
            }
        }
    }
    cout << ans1 << endl << ans2 << endl;
    return 0;
}
