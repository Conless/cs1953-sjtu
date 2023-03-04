#define fileopen freopen("in","r",stdin);printf("freopne here\n")
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using ll = long long;
const int maxn = 1e5 + 10;
//多重背包
int n,m,k,a,b;
int f[maxn],dp[maxn],col[maxn],cnt[maxn],cl,tail = -1,w[maxn],rec[maxn],val[maxn];
int find(int x) {
    if(f[x] == x) return x;
    return f[x] = find(f[x]);
}
int main() {
    //fileopen;
    freopen("1665.in", "r", stdin);
    cin >> n >> m >> k;
    for(int i = 0; i <= n; ++i)
        f[i] = i;
    for(int i = 0; i < k; ++i) {
        scanf("%d%d",&a,&b);
        int x = find(a),y = find(b);
        if(x != y)f[x] = y;
    }
    for(int i = 1; i <= n; ++i) {
        int fa = find(i);
        if(!col[fa]) {
            col[fa] = ++cl;
            cnt[cl] += 1;
        } else {
            cnt[col[fa]] += 1;
        }
    }
    sort(cnt + 1,cnt + cl + 1);
    for(int i = 1; i <= cl; ++i)
        rec[cnt[i]]++;
    for(int i = 1; i <= (int)4e4; ++i) {//rec 的 ind 是这组几个人
        if(rec[i] == 0)continue;
        int c = 1,wei = rec[i],v = i;
        while(wei - c > 0) {
            w[++tail] = c * i;
            wei -= c;
            c <<= 1;
        }
        w[++tail] = wei * i;
    }
    sort(w,w + tail + 1);//w == v in this question
    for(int i = 0; i <= tail; ++i)
        for(int j = 2 * m; j >= w[0]; --j)
            if(j - w[i] >= 0 && (dp[j - w[i]] > 0 || j - w[i] == 0))
                dp[j] = 1;
    int ans = 0;
    for(int i = 0; i <= 2 * m; ++i)
        if(dp[i] > 0 && (abs(i - m) < abs(ans - m) || abs(i - m) == abs(ans - m) && ans > i))
            ans = i;
    cout << ans << endl;
    return 0;
}