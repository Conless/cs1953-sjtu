#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;

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
template <class T1, class T2>
inline void getmin(T1& x, const T2& y) {if (y < x) x = y;}
template <class T1, class T2>
inline void getmax(T1& x, const T2& y) {if (x < y) x = y;}
//char NY[2][10]={"NO\n","YES\n"};//capital?

#ifdef DEBUG
	#define SHOW(x) (cerr<<#x"="<<(x)<<endl,(x))
	#define MSG(s) (cerr<<"MESSAGE: "<<(s)<<endl,0)
#else
	#define SHOW(x) (x)
	#define MSG(s) 0
#endif

#define QUIT cout<<"sad"<<endl,exit(0)
const int N = 1e5 + 5, E = 1e6 + 10;
int head[N], tot = 2, nxt[E], to[E];
ll w[E];
inline void link(int x, int y, int z) {
	nxt[tot] = head[x], to[tot] = y, w[tot] = z, head[x] = tot++;
}
#define iter(x,v) for(int v,e=head[x];v=to[e],e;e=nxt[e])
ll h[N], l[N];
#define dis first
#define id second
ll dis[N];
typedef pair<ll, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > Q;

signed main() {
	IOS;
	int n, e, s, t, lim;
	ll q;
	cin >> n >> e >> s >> t >> lim >> q;
	For(i, 1, n) cin >> h[i] >> l[i];
	For(i, 1, e) {
		int u, v, w;
		cin >> u >> v >> w;
		link(u, v, w), link(v, u, w);
	}
	memset(dis, 0x3f, sizeof(dis));
	if (h[s] > l[s]) { QUIT; }
	dis[s] = 0, Q.push(pii(0, s));
	while (!Q.empty()) {
		pii tp = Q.top();
		Q.pop();
		ll dx = tp.dis;
		int x = tp.id;
		if (dx > lim || dx != dis[x]) { continue; }
		iter(x, v) {
			ll dv = dx + w[e];
			if (dv < dis[v] && dv * q + h[v] <= l[v]) { dis[v] = dv, Q.push(pii(dv, v)); }
		}
	}

	if (dis[t] > lim) { QUIT; }
	cout << dis[t] << endl;

	return cout << flush, 0;
}