// Statement and information
/*
    Author: Conless
    Date: 2022-09-28
    File name: /oi/acmoj/1708.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions


// Templates and namespaces

// Classes


// Funtions

inline int min(int a, int b) { return a < b ? a : b; }


// Main function
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, k, p;
        scanf("%d%d%d%d", &n, &m, &k, &p);
        if (n == p)
        {
            if (k % p == 0)
                printf("YES\n");
            else printf("NO\n");
        }
        else {
            if (k < p)
                printf("NO\n");
            else {
                int exp = min(m, k / p);
                if ((k - exp * p) > (exp - 1) * (n - p))
                    printf("NO\n");
                else printf("YES\n");
            }
        }
    }
    return 0;
}