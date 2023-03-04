#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e3 + 5;
const int MAXM = 8e6 + 5;

class QuickRead {

  public:
    inline char gc() {
        static const int IN_LEN = 1 << 18 | 1;
        static char buf[IN_LEN], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
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

struct Edge {
    int v, next;
} edge[MAXM];

int n, cnt, ti, tot;
int head[MAXN], dfn[MAXN], low[MAXN], ins[MAXN];
int a[MAXN][MAXN];
stack<int> st;

void add_edge(int u, int v) {
    cnt++;
    edge[cnt] = {v, head[u]};
    head[u] = cnt;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ti;
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
            st.pop();
            ins[tp] = 0;
        } while (tp != u);
    }
    return;
}

int main() {
    int T;
    qin >> T;
    while (T--) {
        memset(head, 0, sizeof(head));
        cnt = 0;
        qin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                qin >> a[i][j];
                if (a[i][j]) {
                    add_edge(i, j);
                }
            }
        }
        ti = 0;
        tot = 0;
        while (!st.empty())
            st.pop();
        for (int i = 1; i <= n; i++)
            dfn[i] = low[i] = ins[i] = 0;
        tarjan(1);
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tot++;
                break;
            }
        }
        if (tot > 1)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}