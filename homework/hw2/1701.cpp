// Statement and information
// Author: Conless
// Date: 2022-10-19
// File name: /course/22fall/sjtu/cs1953/homework/hw2/1701.cpp

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions
#define sn segTree[node]
#define sl segTree[sn.lson]
#define sr segTree[sn.rson]

typedef long long ll;

const int MAXN = 3e5 + 5;
const ll MOD = 1e9 + 9;

int n, m;
ll num[MAXN], sum[MAXN], fib[MAXN];

inline void inc(ll &a, ll b) { a = (a + b) % MOD; }

// Templates and namespaces

// Classes
class QuickRead {
  public:
    inline char gc() {
        static const int IN_LEN = 1 << 18 | 1;
        static char buf[IN_LEN], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)),
               s == t ? -1 : *s++;
    }

    template <typename _Tp> inline QuickRead &operator>>(_Tp &num) {
        static char ch, sgn;
        ch = gc();
        sgn = 0;
        for (; !isdigit(ch); ch = gc()) {
            if (ch == -1)
                return *this;
            sgn |= (ch == '-');
        }
        num = 0;
        for (num = 0; isdigit(ch); ch = gc())
            num = num * 10 + (ch ^ '0');
        sgn && (num = -num);
        return *this;
    }
} qin;
class SegmentTree {
  private:
    struct EdgeNode {
        int l, r, len;
        int lson, rson;
        ll data, tag1, tag2;
    } segTree[MAXN << 2];

  public:
    void build(int node, int l, int r) {
        sn.l = l;
        sn.r = r;
        sn.len = r - l + 1;
        sn.tag1 = sn.tag2 = 0;
        if (l == r)
            sn.data = 0;
        else {
            sn.lson = node << 1;
            sn.rson = node << 1 | 1;
            int mid = (l + r) >> 1;
            build(sn.lson, l, mid);
            build(sn.rson, mid + 1, r);
        }
    }

    void pushdown(int node) {
        if (sn.tag1 || sn.tag2) {
            ll cgl1 = sn.tag1, cgl2 = sn.tag2;
            inc(sl.tag1, cgl1);
            inc(sl.tag2, cgl2);
            inc(sl.data, (cgl1 * fib[sl.len] % MOD) +
                             cgl2 * (fib[sl.len + 1] - 1LL) % MOD);
            ll cgr1 = (sn.tag1 * fib[sl.len - 1] % MOD) +
                      (sn.tag2 * fib[sl.len] % MOD),
               cgr2 = (sn.tag1 * fib[sl.len] % MOD) +
                      (sn.tag2 * fib[sl.len + 1] % MOD);
            inc(sr.tag1, cgr1);
            inc(sr.tag2, cgr2);
            inc(sr.data, (cgr1 * fib[sr.len] % MOD) +
                             (cgr2 * (fib[sr.len + 1] - 1LL) % MOD));
            sn.tag1 = sn.tag2 = 0;
        }
    }

    void change(int node, int l, int r) {
        if (sn.l > r || sn.r < l)
            return;
        if (sn.l >= l && sn.r <= r) {
            inc(sn.tag1, fib[sn.l - l + 1]);
            inc(sn.tag2, fib[sn.l - l + 2]);
            inc(sn.data, (fib[sn.r - l + 3] - fib[sn.l - l + 2] + MOD) % MOD);
        } else {
            pushdown(node);
            change(sn.lson, l, r);
            change(sn.rson, l, r);
            sn.data = (sl.data + sr.data) % MOD;
        }
    }

    ll query(int node, int l, int r) {
        if (sn.l > r || sn.r < l)
            return 0;
        if (sn.l >= l && sn.r <= r)
            return sn.data;
        else {
            pushdown(node);
            return (query(sn.lson, l, r) + query(sn.rson, l, r)) % MOD;
        }
    }
} stree;

// Funtions
void pre() {
    fib[0] = 0LL;
    fib[1] = 1LL;
    for (int i = 2; i <= n + 2; i++)
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
}

// Main function
int main() {
    qin >> n >> m;
    for (int i = 1; i <= n; i++) {
        qin >> num[i];
        sum[i] = (sum[i - 1] + num[i]) % MOD;
    }
    pre();
    stree.build(1, 1, n);
    while (m--) {
        int opt, l, r;
        qin >> opt >> l >> r;
        if (opt == 1)
            stree.change(1, l, r);
        else
            printf("%lld\n",
                   (stree.query(1, l, r) + (sum[r] - sum[l - 1] + MOD)) % MOD);
    }
    return 0;
}