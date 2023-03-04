// Statement and information
// Author: Conless
// Date: 2022-10-18
// File name: /course/22fall/sjtu/cs1953/homework/hw2/1721.cpp

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
using std::max;

const int MAXN = 5e3 + 5;

struct Edge {
    int v, next;
} edge[MAXN << 1];

int n, m, res1, res2, ans;
int head[MAXN];
int vis[MAXN], depth[MAXN];
// Templates and namespaces

// Classes

// Funtions
void add_edge(int u, int v) {
    edge[m].v = v;
    edge[m].next = head[u];
    head[u] = m;
    m++;
}

void dfs(int now, int bridge) {
    vis[now] = 1;
    depth[now] = 0;
    int max_depth = 0, sec_depth = 0;
    for (int i = head[now]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (i == bridge || i == (bridge ^ 1))
            continue;
        if (!vis[v]) {
            dfs(v, bridge);
            res1 = max(res1, depth[now] + depth[v] + 1);
            depth[now] = max(depth[now], depth[v] + 1);
        }
    }
}

// Main function
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 0; i < m; i += 2) {
        memset(vis, 0, sizeof(vis));
        memset( depth, 0, sizeof( depth));
        res2 = -1;
        for (int j = 1; j <= n; j++) {
            if (vis[j])
                continue;
            res1 = 1;
            dfs(j, i);
            // printf("%d %d %d\n", i, j, res1);
            if (res2 == -1)
                res2 = res1;
            else {
                ans = max(ans, res1 * res2);
                break;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}