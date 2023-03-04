#include <bits/stdc++.h>

#define sn segTree[node]
#define sl segTree[sn.lson]
#define sr segTree[sn.rson]

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 5;

int n, m, cnt;
int ans[MAXN];

struct Query {
    int l, r;
    int id, op, val;
} q[MAXN], ql[MAXN], qr[MAXN];

class SegmentTree {
  private:
    struct TreeNode {
        int l, r;
        int lson, rson;
        ll tag, rec, sum;
    } segTree[MAXN << 2];

  public:
    void pushdown(int node) {
        if (sn.rec) {
            sn.rec = 0;
            sl.tag = sr.tag = 0;
            sl.sum = sr.sum = 0;
            sl.rec = sr.rec = 1;
        }
        if (sn.tag) {
            sl.tag += sn.tag;
            sr.tag += sn.tag;
            sl.sum += sn.tag * (sl.r - sl.l + 1);
            sr.sum += sn.tag * (sr.r - sr.l + 1);
            sn.tag = 0;
        }
    }
    void pushup(int node) { sn.sum = sl.sum + sr.sum; }
    void reset() {
        segTree[1].rec = 1;
        segTree[1].sum = segTree[1].tag = 0;
    }
    void build(int node, int l, int r) {
        sn.l = l;
        sn.r = r;
        if (l < r) {
            int mid = (l + r) >> 1;
            sn.lson = node << 1;
            sn.rson = node << 1 | 1;
            build(sn.lson, l, mid);
            build(sn.rson, mid + 1, r);
        }
    }
    void add(int node, int left, int right, int num) {
        if (sn.l > right || sn.r < left)
            return;
        if (sn.l >= left && sn.r <= right) {
            sn.tag += num;
            sn.sum += num * (sn.r - sn.l + 1);
            return;
        }
        pushdown(node);
        add(sn.lson, left, right, num);
        add(sn.rson, left, right, num);
        pushup(node);
    }
    ll query(int node, int left, int right) {
        if (sn.l > right || sn.r < left)
            return 0;
        if (sn.l >= left && sr.r <= right)
            return sn.sum;
        pushdown(node);
        return query(sn.lson, left, right) + query(sn.rson, left, right);
    }
} stree;

void solve(int fir, int las, int left, int right) {
    if (left == right) {
        for (int i = fir; i <= las; i++) {
            if (q[i].op == 2)
                ans[q[i].id] = left;
        }
        return;
    }
    int mid = (left + right) >> 1;
    int cntl = 0, cntr = 0, fl = 0, fr = 0;
    stree.reset();
    for (int i = fir; i <= las; i++) {
        if (q[i].op == 1) {
            if (q[i].val > mid) {
                stree.add(1, q[i].l, q[i].r, 1);
                qr[++cntr] = q[i];
            } else {
                ql[++cntl] = q[i];
            }
        } else {
            ll val = stree.query(1, q[i].l, q[i].r);
            if (val < q[i].val) {
                q[i].val -= val;
                fl = 1;
                ql[++cntl] = q[i];
            } else {
                fr = 1;
                qr[++cntr] = q[i];
            }
        }
    }
    for (int i = 1; i <= cntl; i++)
        q[fir + i - 1] = ql[i];
    for (int i = cntl + 1; i <= cntl + cntr; i++)
        q[fir + i - 1] = qr[i - cntl];
    if (fl)
        solve(fir, fir + cntl - 1, left, mid);
    if (fr)
        solve(fir + cntl, las, mid + 1, right);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &q[i].op, &q[i].l, &q[i].r, &q[i].val);
        if (q[i].op == 2)
            q[i].id = ++cnt;
    }
    stree.build(1, 1, n);
    solve(1, m, -n, n);
    for (int i = 1; i <= cnt; i++)
        printf("%d\n", ans[i]);
    return 0;
}