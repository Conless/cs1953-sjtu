#define fileopen freopen("in","r",stdin);cout << "freopen here" << endl
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e6 + 10;
ll sum[maxn << 2],lz[maxn << 2],cnt[maxn << 2],inisum[maxn << 2];
char a[maxn];
int n,m,l,r;
template<class T>
inline void read(T &res){
    ll x = 0,w = 1;char c = getchar();
    while(c > '9' || c < '0'){
        if(c == '-')w = -1;c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x * 10 + c - '0');c = getchar();
    } res = x * w;
}
void pushup(int rt) {
    cnt[rt] = cnt[rt << 1] + cnt[rt << 1 | 1];
    inisum[rt] = inisum[rt << 1] + inisum[rt << 1 | 1];
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void build(int rt,int l,int r) {
    if(l == r) {
        cnt[rt] = (a[l] == '0');
        if(cnt[rt]) {
            sum[rt] = l;
        }
        inisum[rt] = l;
        return ;
    }
    int m = l + r >> 1;
    build(rt << 1,l,m);
    build(rt << 1 | 1,m + 1,r);
    pushup(rt);
}
//lz[] == 1 means there is a need to reverse
void pushdown(int rt,int l,int r) {
    if(lz[rt] == 0) 
        return ;
    int m = l + r >> 1;
    cnt[rt << 1] = m - l + 1 - cnt[rt << 1];
    cnt[rt << 1 | 1] = r - m - 1 + 1 - cnt[rt << 1 | 1];
    sum[rt << 1] = inisum[rt << 1] - sum[rt << 1];
    sum[rt << 1 | 1] = inisum[rt << 1 | 1] - sum[rt << 1 | 1];
    lz[rt << 1] ^= 1;
    lz[rt << 1 | 1] ^= 1;//  ??
    lz[rt] = 0;
}
void upd(int rt,int l,int r,int x,int y) {
    pushdown(rt,l,r);
    if(x <= l && r <= y) {
        lz[rt] ^= 1;
        cnt[rt] = r - l + 1 - cnt[rt];  //no need to down to the all 0 or all 1 interspace
        sum[rt] = inisum[rt] - sum[rt]; //directly change !
        return ;
    }
    int m = l + r >> 1;
    if(y <= m)upd(rt << 1,l,m,x,y);
    else if(x > m) upd(rt << 1 | 1,m + 1,r,x,y);
    else upd(rt << 1,l,m,x,y),
        upd(rt << 1 | 1,m + 1,r,x,y);
    pushup(rt);
}
int main() {
    //fileopen;
    cin >> n >> m;
    scanf("%s",a + 1);
    build(1,1,n);
    printf("%lld\n",2 * sum[1] - cnt[1] * cnt[1]);
    for(int i = 0; i < m; ++i) {
        read(l);read(r);
        if(l > r)
            swap(l,r);
        upd(1,1,n,l,r);
        printf("%lld\n",2 * sum[1] - cnt[1] * cnt[1]);
    }
    return 0;
}