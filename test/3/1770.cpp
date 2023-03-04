#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXM = 5e5 + 5;
const int INF = 1e9;

typedef long long ll;

int n, m;
int cnt, ti;
int head[MAXN], h[MAXN], fa[MAXN], mson[MAXN], siz[MAXN];
int key[MAXN], tp[MAXN], las[MAXN];
int from_org[MAXN], fromw_org[MAXN], from[MAXN], fromw[MAXN];
int ans[MAXN];

struct Edge_org {
    int u, v, w, id, sel;
} edge_org[MAXM];
struct Edge {
    int v, w, id, next;
} edge[MAXN << 1];

void dfs(int u, int las) {
    int maxsiz = 0;
    siz[u] = 1;
    fa[u] = las;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (v == las)
            continue;
        h[v] = h[u] + 1;
        from_org[v] = edge[i].id;
        fromw_org[v] = edge[i].w;
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[v] > maxsiz) {
            maxsiz = siz[v];
            mson[u] = v;
        }
    }
}

void build(int u, int last, int top) {
    key[u] = ++ti;
    from[ti] = from_org[u];
    fromw[ti] = fromw_org[u];
    tp[u] = top;
    if (mson[u]) {
        build(mson[u], u, top);
    }
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (v == last || v == mson[u])
            continue;
        build(v, u, v);
    }
    las[u] = ti;
}

#define sn segTree[node]
#define sl segTree[sn.lson]
#define sr segTree[sn.rson]

class SegmentTree {
  private:
    struct EdgeNode {
        int l, r;
        int lson, rson;
        int id, tag, data;
    } segTree[MAXN << 2];

  public:
    void build(int node, int l, int r) {
        sn.l = l;
        sn.r = r;
        sn.tag = INF;
        if (l == r) {
            sn.id = from[l];
            sn.data = fromw[l];
        } else {
            sn.lson = node << 1;
            sn.rson = node << 1 | 1;
            int mid = (l + r) >> 1;
            build(sn.lson, l, mid);
            build(sn.rson, mid + 1, r);
            sn.data = max(sl.data, sr.data);
        }
    }

    void pushdown(int node) {
        if (sn.tag != INF) {
            sl.tag = min(sl.tag, sn.tag);
            sr.tag = min(sr.tag, sn.tag);
            return;
        }
    }

    bool change(int node, int l, int r, int val) {
        if (sn.l > r || sn.r < l)
            return 0;
        if (sn.l >= l && sn.r <= r) {
            sn.tag = min(sn.tag, val);
            return val <= sn.data;
        } else {
            pushdown(node);
            return change(sn.lson, l, r, val) | change(sn.rson, l, r, val);
        }
    }

    void init(int node) {
        if (sn.l == sn.r) {
            ans[sn.id] = sn.tag > sn.data;
        } else {
            pushdown(node);
            init(sn.lson);
            init(sn.rson);
        }
    }
} stree;

void add_edge(int u, int v, int w, int id) {
    cnt++;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].id = id;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

bool edit(int x, int y, ll val) {
    bool res = 0;
    while (tp[x] != tp[y]) {
        if (h[tp[x]] < h[tp[y]])
            swap(x, y);
        res |= stree.change(1, key[tp[x]], key[x], val);
        x = fa[tp[x]];
    }
    if (key[x] > key[y])
        swap(x, y);
    res |= stree.change(1, key[mson[x]], key[y], val);
    return res;
}

int find_fa[MAXN];

inline int find(int x) { return x == find_fa[x] ? x : find_fa[x] = find(find_fa[x]); }

void Kruskal() {
    sort(edge_org + 1, edge_org + m + 1, [](Edge_org a, Edge_org b) { return a.w < b.w; });
    for (int i = 1; i <= n; i++)
        find_fa[i] = i;
    for (int i = 1, j = 0; i <= m && j < n; i++) {
        int fu = find(edge_org[i].u), fv = find(edge_org[i].v);
        if (fu != fv) {
            find_fa[fu] = fv;
            add_edge(edge_org[i].u, edge_org[i].v, edge_org[i].w, edge_org[i].id);
            add_edge(edge_org[i].v, edge_org[i].u, edge_org[i].w, edge_org[i].id);
            edge_org[i].sel = 1;
            j++;
        } else {
            if (edge_org[i].w > edge_org[i - 1].w)
                edge_org[i].sel = -1;
        }
    }
}

int main() {
    // freopen("1770.in", "r", stdin);
    // freopen("1770.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge_org[i].u >> edge_org[i].v >> edge_org[i].w;
        edge_org[i].id = i;
    }
    Kruskal();
    int rt = 1;
    h[rt] = 1;
    dfs(rt, 0);
    build(rt, 0, rt);
    stree.build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        if (!edge_org[i].sel) {
            if (edit(edge_org[i].u, edge_org[i].v, edge_org[i].w))
                ans[edge_org[i].id] = 0;
            else
                ans[edge_org[i].id] = -1;
        } else if (edge_org[i].sel == -1)
            ans[edge_org[i].id] = -1;
    }
    stree.init(rt);
    for (int i = 1; i <= m; i++) {
        if (ans[i] == 1)
            cout << "any\n";
        else if (!ans[i])
            cout << "at least one\n";
        else
            cout << "none\n";
    }
    return 0;
}