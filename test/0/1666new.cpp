// Statement and information
// Author: Conless
// Date: 2022-10-12
// File name: /oi/acmoj/1666new.cpp

// Headers
#include <iostream>
#include <cstdio>
#include <type_traits>
#include <utility>

// Constants, global variables and definitions

#define sn segTree[node]

inline void inc(int &x, int y) { x += y; }

const int MAXN = 1e5 + 5;

int n, m, p;
int ans[MAXN];

// Templates and namespaces
struct Edge {
    int l, r;
    int v, next, key;
    int friend_edge, not_tree_edge;
};
class SegmentTree {
  private:
    struct EdgeNode {
        int l, r;
        int lson, rson;
        int data, tag;
    } segTree[MAXN << 2];

  public:
    void build(int node, int l, int r) {
        sn.l = l;
        sn.r = r;
        sn.tag = 0;
        if (l == r)
            sn.data = 0;
        else {
            sn.lson = node << 1;
            sn.rson = node << 1 | 1;
            int mid = (l + r) >> 1;
            build(sn.lson, l, mid);
            build(sn.rson, mid + 1, r);
            sn.data = (segTree[sn.lson].data + segTree[sn.rson].data);
        }
    }

    void pushdown(int node) {
        if (sn.tag) {
            inc(segTree[sn.lson].tag, sn.tag);
            inc(segTree[sn.lson].data,
                (segTree[sn.lson].r - segTree[sn.lson].l + 1) * sn.tag);
            inc(segTree[sn.rson].tag, sn.tag);
            inc(segTree[sn.rson].data,
                (segTree[sn.rson].r - segTree[sn.rson].l + 1) * sn.tag);
            sn.tag = 0;
        }
    }

    void change(int node, int l, int r, int val) {
        if (sn.l > r || sn.r < l)
            return;
        if (sn.l >= l && sn.r <= r) {
            inc(sn.tag, val);
            inc(sn.data, (sn.r - sn.l + 1) * val);
        } else {
            pushdown(node);
            change(sn.lson, l, r, val);
            change(sn.rson, l, r, val);
            sn.data = (segTree[sn.lson].data + segTree[sn.rson].data);
        }
    }

    int query(int node, int l, int r) {
        if (sn.l > r || sn.r < l)
            return 0;
        if (sn.l >= l && sn.r <= r)
            return sn.data;
        else {
            pushdown(node);
            return (query(sn.lson, l, r) + query(sn.rson, l, r));
        }
    }

};
class TreeChain {
  private:
    const int rt = 1;

    int node_height[MAXN], par[MAXN];
    int tree_size[MAXN], wgt_son[MAXN];

    int ebcc_tag[MAXN], ebcc_sum[MAXN], brg_tag[MAXN];

    Edge edge[MAXN << 1];
    int edge_cnt, head[MAXN], path_key_new[MAXN], path_key_org[MAXN];

    SegmentTree stree;
    int node_cnt, node_key[MAXN], last_key[MAXN], tp_chain[MAXN];

  public:
    void Output() {
        for (int i = 1; i <= n; i++)
            printf("%d: %d %d %d %d %d %d\n", i, node_height[i], par[i], ebcc_tag[i], brg_tag[i], stree.query(1, node_key[i], node_key[i]), path_key_org[i]);
    }

  private:
    void AddEdge(int u, int v, int key, int l, int r) {
        edge_cnt++;
        edge[edge_cnt].v = v;
        edge[edge_cnt].next = head[u];
        edge[edge_cnt].key = key;
        edge[edge_cnt].l = l;
        edge[edge_cnt].r = r;
        if (l == u)
            edge[edge_cnt].friend_edge = edge_cnt + 1;
        else edge[edge_cnt].friend_edge = edge_cnt - 1;
        head[u] = edge_cnt;
    }
    void BuildWgt(int now, int las) {
        int max_size = 0;
        tree_size[now] = 1;
        par[now] = las;
        for (int i = head[now]; i; i = edge[i].next) {
            int v = edge[i].v;
            if (v == las || edge[i].not_tree_edge)
                continue;
            if (node_height[v]) {
                edge[i].not_tree_edge = edge[edge[i].friend_edge].not_tree_edge = 1;
                if (node_height[v] < node_height[now]) {
                    ebcc_tag[v] = -1;
                    ebcc_tag[now] = 1;
                } else {
                    ebcc_tag[v] = 1;
                    ebcc_tag[now] = -1;
                }
                continue;
            }
            node_height[v] = node_height[now] + 1;
            path_key_new[v] = i;
            path_key_org[v] = edge[i].key;
            BuildWgt(v, now);
            tree_size[now] += tree_size[v];
            if (tree_size[v] > max_size) {
                max_size = tree_size[v];
                wgt_son[now] = v;
            }
        }
    }
    void BuildTree(int now, int las, int top) {
        node_key[now] = ++node_cnt;
        tp_chain[now] = top;
        ebcc_sum[now] = ebcc_tag[now];
        if (wgt_son[now]) {
            BuildTree(wgt_son[now], now, top);
            ebcc_sum[now] += ebcc_sum[wgt_son[now]];
        }
        for (int i = head[now]; i; i = edge[i].next) {
            int v = edge[i].v;
            if (par[v] != now || wgt_son[now] == v || edge[i].not_tree_edge)
                continue;
            BuildTree(v, now, v);
            ebcc_sum[now] += ebcc_sum[v];
        }
        if (ebcc_sum[now])
            brg_tag[now] = 0;
        else brg_tag[now] = 1;
        last_key[now] = node_cnt;
    }

  public:
    void Build() {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            AddEdge(u, v, i, u, v);
            AddEdge(v, u, i, u, v);
        }
        node_height[rt] = 1;
        BuildWgt(rt, 0);
        BuildTree(rt, 0, rt);
        stree.build(1, 1, n);
    }
    void EditPath(int x, int y, int val) {
        while (tp_chain[x] != tp_chain[y]) {
            if (node_height[tp_chain[x]] < node_height[tp_chain[y]])
                std::swap(x, y);
            stree.change(1, node_key[tp_chain[x]], node_key[x], val);
            x = par[tp_chain[x]];
        }
        if (node_key[x] > node_key[y])
            std::swap(x, y);
        stree.change(1, node_key[x], node_key[y], val);
    }
    int LCA(int x, int y) {
        while (tp_chain[x] != tp_chain[y]) {
            if (node_height[tp_chain[x]] < node_height[tp_chain[y]])
                std::swap(x, y);
            x = par[tp_chain[x]];
        }
        if (node_height[x] > node_height[y])
            std::swap(x, y);
        return x;
    }
    void CalculateResult(int now) {
        if (now != rt) {
            int res = stree.query(1, node_key[now], node_key[now]);
            if (res && brg_tag[now]) {
                if ((res == 1 && edge[path_key_new[now]].r == now) ||
                    (res == -1 && edge[path_key_new[now]].l == now))
                    ans[path_key_org[now]] = -1;
                else ans[path_key_org[now]] = 1;
            }
        }
        for (int i = head[now]; i; i = edge[i].next) {
            int v = edge[i].v;
            if (par[v] != now)
                continue;
            CalculateResult(v);
        }
    }
} t;

// Classes

// Funtions

// Main function
int main() {
    // freopen("1666new.in", "r", stdin);
    t.Build();
    scanf("%d", &p);
    while (p--) {
        int x, y;
        scanf("%d%d", &x, &y);
        int lca = t.LCA(x, y);
        t.EditPath(x, lca, 1);
        t.EditPath(lca, y, -1);
    }
    t.CalculateResult(1);
    for (int i = 1; i <= m; i++) {
        if (!ans[i]) {
            printf("B");
        } else {
            if (ans[i] == 1)
                printf("R");
            else printf("L");
        }
    }
    printf("\n");
    // t.Output();
    return 0;
}