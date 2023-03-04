#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 3;
int n; ll p[65], ans;
pair<int, ll> a[maxn];
signed main() {
    freopen("1703.in", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i].second >> a[i].first;
	sort(a + 1, a + n + 1, greater< pair<int, ll> >());
	for (int i = 1; i <= n; ++i) {
		ll &x = a[i].second;
		for (int j = 62; j >= 0; --j) {
			if ((x >> j) & 1ll) {
				if (p[j]) x ^= p[j];
				else {
					p[j] = x;
					ans += (ll)a[i].first;
					break;
				}
			}
		}
	}
	// cout << p[0] << " " << p[1] << endl;
	cout << ans << endl;
	return 0;
}