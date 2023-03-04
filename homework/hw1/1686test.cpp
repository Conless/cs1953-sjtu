#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
char s[MAXN];

int main()
{
    int n, cnt = 0;
    cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++)
        cnt += (s[i] - '0') ^ 1;
    while (cnt)
    {
        int num = s[cnt] - '0';
        s[cnt] = (num ^ 1) + '0';
        if (num)
            cnt++;
        else cnt--;
        cout << s + 1 << endl;
    }
    return 0;
}