#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e6 + 5;

struct Edge {
    int v, next;
} edge[MAXN];

int n, m, cnt, tim, tot;
int head[MAXN], low[MAXN], dfn[MAXN], ins[MAXN], col[MAXN];
stack<int> st;

void add_edge(int u, int v) {
    cnt++;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
    return;
}

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
    if (low[u] == dfn[u]) {
        tot++;
        int tp;
        do {
            tp = st.top();
            ins[tp] = 0;
            col[tp] = tot;
            st.pop();
        } while (tp != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, z, w;
        cin >> x >> y >> z >> w;
        if (y == 1 && w == 1) {
            add_edge(x + n, z);
            add_edge(z + n, x);
        } else if (y == 1 && w == 0) {
            add_edge(x + n, z + n);
            add_edge(z, x);
        } else if (y == 0 && w == 1) {
            add_edge(x, z);
            add_edge(z + n, x + n);
        } else if (y == 0 && w == 0) {
            add_edge(x, z + n);
            add_edge(z, x + n);
        }
    }
    for (int i = 1; i <= (n << 1); i++) {
        if (!dfn[i])
            tarjan(i);
    }
    for (int i = 1; i <= n; i++) {
        if (col[i] == col[i + n]) {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
    for (int i = 1; i <= n; i++)
        printf("%d ", col[i] < col[i + n]);
    printf("\n");
    return 0;
}