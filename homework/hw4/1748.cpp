#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e3 + 5;
const int MAXM = 1e5 + 5;

bitset<MAXM << 1> pr;
bitset<MAXN> vis;

int n, mx, cnt;
int a[MAXN], match[MAXN], head[MAXN];
vector<int> prime, num[2];

struct Edge {
    int v, next;
} edge[MAXN * MAXN];

void add_edge(int u, int v) {
    cnt++;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void pre() {
    for (int i = 2; i <= mx * 2; i++) {
        if (pr[i])
            prime.push_back(i);
        for (int j = 0; j < prime.size(); j++) {
            if (i * prime[j] >= mx * 2)
                break;
            pr[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
}

bool dfs(int id) {
    // cout << id << endl;
    for (int i = head[id]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (vis[v])
            continue;
        vis[v] = 1;
        if (!match[v] || dfs(match[v])) {
            match[v] = id;
            return 1;
        }
    }
    return 0;
}

int main() {
    // freopen("1748.in", "r", stdin);
    // freopen("1748.out", "w", stdout);
    ios::sync_with_stdio(false);
    pr.set();
    pr[1] = pr[0] = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    pre();
    for (int i = 1; i <= n; i++) {
        num[a[i] % 2].push_back(i);
        for (int j = 1; j < i; j++) {
            if (pr[a[i] + a[j]]) {
                add_edge(i, j);
                add_edge(j, i);
            }
        }
    }
    if (num[0].size() < num[1].size())
        num[0].swap(num[1]);
    int ans = 0;
    for (auto i : num[0]) {
        vis.reset();
        if (dfs(i))
            ans++;
    }
    cout << n - ans << '\n';
    return 0;
}