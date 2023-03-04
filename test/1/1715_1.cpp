// Statement and information
// Author: Conless
// Date: 2022-11-04
// File name: /course/22fall/sjtu/cs1953/test/1/1715_1.cpp

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 5;

int k, q, cnt;

string m, s;
string pt[MAXN];
ll lenm, len[MAXN];
ll pos_left, pos_mid;

void PreCount() {
    lenm = m.size();
    cnt = 1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '$') {
            len[cnt] = pt[cnt].length();
            cnt++;
        }
        else pt[cnt] += s[i];
    }
    len[cnt] = pt[cnt].length();
}

void SolveMidIns(ll l, ll r) {
    if (l < pos_left) {
        if (r < pos_left) {
            for (ll i = l; i <= r; i++)
                putchar(pt[1][i % len[1]]);
        } else {
            for (ll i = l; i < pos_left; i++)
                putchar(pt[1][i % len[1]]);
            if (r < pos_mid) {
                for (ll i = pos_left; i <= r; i++)
                    putchar(m[i - pos_left]);
            } else {
                for (ll i = pos_left; i < pos_mid; i++)
                    putchar(m[i - pos_left]);
                for (ll i = pos_mid; i <= r; i++)
                    putchar(pt[2][(i - pos_mid) % len[2]]);
            }
        }
    } else if (l < pos_mid) {
        if (r < pos_mid) {
            for (ll i = l; i <= r; i++)
                putchar(m[i - pos_left]);
        } else {
            for (ll i = l; i < pos_mid; i++)
                putchar(m[i - pos_left]);
            for (ll i = pos_mid; i <= r; i++)
                putchar(pt[2][(i - pos_mid) % len[2]]);
        }
    } else {
        for (ll i = l; i <= r; i++)
            putchar(pt[2][(i - pos_mid) % len[2]]);
    }
}

const int MAXLEN = 1e5 + 5;

string solve(int depth, int mlen) {
    if (depth == 0)
        return m;
    string tt = pt[1];
    for (int i = 2; i <= cnt; i++) {
        if (tt.size() > mlen)
            break;
        tt += solve(depth - 1, mlen - tt.size());
        if (tt.size() > mlen)
            break;
        tt += pt[i];
    }
    return tt;
}

int main() {
    // freopen("1715.in", "r", stdin);
    // freopen("1715.out", "w", stdout);
    cin >> m;
    cin >> s;
    scanf("%d%d", &k, &q);
    PreCount();
    if (cnt == 2) {
        while (q--) {
            ll l, r;
            scanf("%lld%lld", &l, &r);
            l--;
            r--;
            pos_left = len[1] * k;
            pos_mid = pos_left + lenm;
            SolveMidIns(l, r);
            printf("\n");
        }
    } else {
        string ans = solve(k, MAXLEN);
        while (q--) {
            int l, r;
            scanf("%d%d", &l, &r);
            l--;
            r--;
            for (int i = l; i <= r; i++)
                putchar(ans[i]);
            printf("\n");
        }
    }
    return 0;
}