#define fileopen freopen("in","r",stdin);cout << "freopen here" << endl
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5 + 10;
int n,ind[maxn],tmp;
map<int,int> rec;
int main() {
    //fileopen;
    freopen("1716.in", "r", stdin);
    freopen("1716test.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        scanf("%d",&tmp);
        ind[tmp] = i;
        rec.insert(make_pair(i,tmp));
    }
    for(int i = n; i >= 1; --i) {
        auto itr = rec.find(ind[i]);
        if(itr == rec.end())continue;
        auto ptr = ++itr;
        if(ptr == rec.end())continue;
        --itr;
        printf("%d %d ",itr->second,ptr->second);
        rec.erase(itr);
        rec.erase(ptr);
    }
    return 0;
}