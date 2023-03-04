#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pii;
#define IOS ios::sync_with_stdio(0)
#define For(i,a,b) for (int i=(a),_b=(b);i<=_b;i++)
#define FOr For
#define Iter(i,a,b) for (int i=(a),_b=(b);i<_b;i++)
#define Downto(i,a,b) for (int i=(a),_b=(b);i>=_b;i--)
#define set0(a) memset(a,0,sizeof(a))
#define set0n(a,n) memset(a,0,sizeof((a)[0])*(n+1))
#define pb push_back
#define mkp make_pair
#define all(a) (a).begin(),(a).end()
template <class T1,class T2>
inline void getmin(T1& x,const T2& y){if (y<x) x=y;}
template <class T1,class T2>
inline void getmax(T1& x,const T2& y){if (x<y) x=y;}
//char NY[2][10]={"NO\n","YES\n"};//capital?

#ifdef DEBUG
#define SHOW(x) (cerr<<#x"="<<(x)<<endl,(x))
#define MSG(s) (cerr<<"MESSAGE: "<<(s)<<endl,0)
#else
#define SHOW(x) (x)
#define MSG(s) 0
#endif

const int N=1e5+5;
ll t[N],d[N];

signed main(){
    freopen("1014.in", "r", stdin);
	IOS;
	int n;cin>>n;
	For(i,1,n) cin>>t[i],d[i]-=t[i]-t[i-1];
	For(i,1,n) cin>>t[i],d[i]+=t[i]-t[i-1];
	ll pos=0,neg=0;
	For(i,1,n) (d[i]>0?pos:neg)+=d[i];
	cout<<max(pos,-neg)<<endl;
	
	return cout<<flush,0;
}