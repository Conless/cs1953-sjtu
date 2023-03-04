// Statement and information
// Author: Conless
// Date: 2022-10-12
// File name: /1713.cpp

// Headers
#include <algorithm>
#include <bits/stdc++.h>

// Constants, global variables and definitions
typedef long long ll;

ll n, m, k, ans;
ll fac[14], lucky_num[1025];
int used[20];

// Templates and namespaces

// Classes

// Funtions
void pre1() {
    fac[0] = 1LL;
    for (ll i = 1LL; i <= 13LL; i++)
        fac[i] = fac[i - 1] * i;
}
void pre2() {
    for (int i = 1; i <= 9; i++) {
        ll maxt = 1 << i;
        for (ll j = 0; j < maxt; j++) {
            ll res = 0, j1 = j;
            for (int k = 1; k <= i; k++) {
                res = res * 10LL;
                if (j1 & 1)
                    res += 7LL;
                else
                    res += 4LL;
                j1 >>= 1;
            }
            lucky_num[++m] = res;
        }
    }
    std::sort(lucky_num + 1, lucky_num + m + 1);
}

int CountBefore1() {
    int pos = std::lower_bound(fac + 1, fac + 14, k) - fac;
    if (fac[pos] == k)
        return pos;
    else return pos - 1;
}
ll CountBefore2(ll max_num) {
    int pos =
        std::lower_bound(lucky_num + 1, lucky_num + m + 1, max_num) - lucky_num;
    if (lucky_num[pos] == max_num)
        return pos;
    return pos - 1;
}
int JudgeLuckyNum(ll num) { return lucky_num[CountBefore2(num)] == num; }

// Main function
int main() {
    // freopen("1713.out", "w", stdout);
    pre1();
    pre2();
    std::cin >> n >> k;
    if (n <= 13 && k > fac[n]) {
        printf("-1\n");
        return 0;
    }
    k--;
    int orgpos = CountBefore1() + 1;
    int chpos = n - orgpos;
    ans = CountBefore2(chpos);
    // for (int i = 1; i <= chpos; i++)
    //     printf("%d ", i);
    for (int i = orgpos - 1; i >= 0; i--) {
        int sel_here = k / fac[i] + 1;
        for (int j = 1; j <= sel_here; j++)
            sel_here += used[j];
        used[sel_here] = 1;
        ans += JudgeLuckyNum(chpos + sel_here) & JudgeLuckyNum(chpos + (orgpos - i));
        k %= fac[i];
        // printf("%d ", chpos + sel_here);
    }
    // printf("\n");
    printf("%lld\n", ans);
    return 0;
}