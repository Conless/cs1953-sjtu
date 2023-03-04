// Statement and information
// Author: Conless
// Date: 2022-11-11
// File name: /course/22fall/sjtu/cs1953/test/2/1740_1.cpp

#include <bits/stdc++.h>

#define anc first
#define son second
#define pr pair<int, int> 

using namespace std;

const int MAXN = 1e5 + 5;

class RevUnionSet {
  private:
    int n, cnt;
    int fa[MAXN], siz[MAXN];
    stack<pr> his;

  public:
    void reset(int n) {
        n = n;
        for (int i = 1; i <= n; i++)
            fa[i] = i, siz[i] = 1;
        while (!his.empty())
            his.pop();
    }
    inline int his_size() { return his.size(); }
    inline int get_size(int x) { return siz[x]; }
    inline int find(const int &x) {
        if (fa[x] == x)
            return x;
        return find(fa[x]);
    }
    inline void unionn(const int &x, const int &y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (siz[fx] > siz[fy])
                swap(fx, fy);
            fa[fx] = fy;
            siz[fy] += siz[fx];
            his.push({fy, fx});
        }
    }
    inline void reverse(const int &his_cnt) {
        int dif_siz = his.size() - his_cnt;
        while (dif_siz--) {
            pr now = his.top();
            his.pop();
            fa[now.son] = now.son;
            siz[now.anc] -= siz[now.son];
        }
    }
} st;

struct Edge {
    int u, v, w;
    bool operator<(const Edge &x) const { return w < x.w; }
};
struct Query {
    int x, y, data, id;
};

int n, m;
int ans[MAXN];
vector<Edge> e;

void solve(int l, int r, const vector<Query> q) {
    if (q.empty())
        return;
    if (l == r) {
        for (auto now : q)
            ans[now.id] = l;
        return;
    }
    int mid = (l + r) >> 1, org_siz = st.his_size();
    auto pos = lower_bound(e.begin(), e.end(), (Edge){0, 0, l});
    while (pos->w <= mid) {
        st.unionn(pos->u, pos->v);
        pos++;
    }
    vector<Query> ll, rr;
    for (auto now : q) {
        int fx = st.find(now.x), fy = st.find(now.y);
        int sum_siz = st.get_size(fx);
        if (fx != fy)
            sum_siz += st.get_size(fy);
        if (now.data > sum_siz)
            rr.push_back(now);
        else
            ll.push_back(now);
    }
    solve(mid + 1, r, rr);
    st.reverse(org_siz);
    solve(l, mid, ll);
}
int main() {
    // freopen("1740.in", "r", stdin);
    // freopen("1740.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    st.reset(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e.push_back({u, v, i});
    }
    int Q;
    cin >> Q;
    vector<Query> q;
    for (int i = 1; i <= Q; i++) {
        int x, y, data;
        cin >> x >> y >> data;
        q.push_back({x, y, data, i});
    }
    solve(e[0].w, e[m - 1].w, q);
    for (int i = 1; i <= Q; i++)
        cout << ans[i] << '\n';
    return 0;
}