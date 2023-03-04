#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;
    int a[105];
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int ans = 0;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i; j++)
            if (a[i] > a[j]) ans++;
    cout << ans << endl;
}