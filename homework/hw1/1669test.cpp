#define fileopen freopen("in","r",stdin);printf("freopne here\n")
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using ll = long long;
const int maxn = 5e2 + 5;
int w[maxn][maxn],a[maxn];
int dp[maxn][maxn],n,m;
int main() {
    //fileopen;
    freopen("1669.in", "r", stdin);
    cin >> n >> m;
    for(int i = 2; i <= n; ++i) {
        scanf("%d",a + i);
        a[i] = a[i - 1] + a[i];
    }
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j) {
            w[i][j] = w[i][j - 1] + a[j] - a[i + j >> 1];
        }
    memset(dp,0x3f3f3f3f,sizeof(dp));
    for(int i = 1; i <= n; ++i) {
        dp[i][1] = w[1][i];
        //cout << w[1][i] << " ";
    }
    //for(int i = 1; i <= n; ++i)
    //    for(int j = 1; j <= m; ++j)
    //        if(i <= j)dp[i][j] = 0;
    for(int j = 2; j <= m; ++j) {
        dp[j][j] = 0;
        for(int i = j + 1; i <= n; ++i) {
            for(int k = j - 1; k < i; ++k) {//从太小开始没意义,反正回到 0
                dp[i][j] = min(dp[i][j],dp[k][j - 1] + w[k + 1][i]);
            }
        }
    }
    cout << dp[n][m] << endl;
    std::cout << clock();
    return 0;
}