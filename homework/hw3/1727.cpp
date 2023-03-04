// Statement and information
// Author: Conless
// Date: 2022-10-26
// File name: /course/22fall/sjtu/cs1953/homework/hw3/1727.cpp

// Headers
#include <bits/stdc++.h>

typedef long long ll;
const int MAXN = 1e5 + 5;

ll n, tot, avg, ans;
ll data[MAXN], sum[MAXN], res[MAXN];

// Main function
int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &data[i]);
        tot += data[i];
    }
    ans = tot * n;
    avg = tot / n;
    for (int i = 1; i <= n; i++) {
        data[i] -= avg;
        sum[i] = sum[i - 1] + data[i];
    }
    std::sort(sum + 1, sum + n + 1);
    for (int i = 1; i <= n; i++)
        res[i] = res[i - 1] + sum[i];
    for (ll i = 1; i <= n; i++)
        ans = std::min(ans, (res[n] - n * sum[i]) - (res[i] - i * sum[i]) - (res[i - 1] - (i - 1) * sum[i]));
    printf("%lld\n", ans);
    return 0;
}