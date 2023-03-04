// Statement and information
// Author: Conless
// Date: 2022-11-11
// File name: /course/22fall/sjtu/cs1953/test/2/1743_1.cpp

#include <bits/stdc++.h>
#include <math.h>

using namespace std;

const int MAXN = 50005;

int n, m, q, e, len;
int data_sync[MAXN];
int data[MAXN], ans[MAXN];
int fir[MAXN], las[MAXN];

struct Query {
    int l, r, t, id, ll, rr;
    Query() {}
    Query(int l, int r, int t, int id) : l(l), r(r), t(t), id(id), ll(l / len), rr(r / len) {}
    bool operator<(const Query &x) const {
        if (ll != x.ll)
            return ll < x.ll;
        if (rr != x.rr)
            return rr < x.rr;
        if (t != x.t)
            return t < x.t;
        return id < x.id;
    }
} Q[MAXN];

struct Edit {
    int x, y, yy;
} E[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    len = sqrt(n);
    for (int i = 1; i <= n; i++)
        cin >> data[i], data_sync[i] = data[i];
    while (m--) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            E[++e] = {x, y, data_sync[x]};
            data_sync[x] = y;
        } else {
            q++;
            Q[q] = {x, y, e, q};
        }
    }
    sort(Q + 1, Q + q + 1);
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= q; i++) {
        while (t < Q[i].t) {
            t++;
            if (E[t].x >= l && E[t].x <= r) {
                if (fir[E[t].yy] == E[t].x) {
                    fir[E[t].yy] = 0;
                    for (int j = E[t].x; j <= r; j++)
                        if (data[j] == E[t].yy) {
                            fir[E[t].yy] = j;
                            break;
                        }
                }
                if (las[E[t].yy] == E[t].x) {
                    las[E[t].yy] = 0;
                    for (int j = E[t].x; j >= l; j--)
                        if (data[j] == E[t].yy) {
                            las[E[t].yy] = j;
                            break;
                        }
                }
                if (fir[E[t].y] > E[t].x || !fir[E[t].y])
                    fir[E[t].y] = E[t].x;
                if (las[E[t].y] < E[t].x || !las[E[t].y])
                    las[E[t].y] = E[t].x;
            }
            data[E[t].x] = E[t].y;
        }
        while (t > Q[i].t) {
            if (E[t].x >= l && E[t].x <= r) {
                if (fir[E[t].y] == E[t].x) {
                    fir[E[t].y] = 0;
                    for (int j = E[t].x; j <= r; j++)
                        if (data[j] == E[t].y) {
                            fir[E[t].y] = j;
                            break;
                        }
                }
                if (las[E[t].y] == E[t].x) {
                    las[E[t].y] = 0;
                    for (int j = E[t].x; j >= l; j--)
                        if (data[j] == E[t].y) {
                            las[E[t].y] = j;
                            break;
                        }
                }
                if (fir[E[t].yy] > E[t].x || !fir[E[t].yy])
                    fir[E[t].yy] = E[t].x;
                if (las[E[t].yy] < E[t].x || !las[E[t].yy])
                    las[E[t].yy] = E[t].x;
            }
            data[E[t].x] = E[t].yy;
            t--;
        }
    }
    return 0;
}
