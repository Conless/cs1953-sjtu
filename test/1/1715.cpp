// Statement and information
// Author: Conless
// Date: 2022-10-12
// File name: /oi/acmoj/1715.cpp

// Headers
#include <bits/stdc++.h>

using std::string;

// Constants, global variables and definitions
const int MAXN = 1e5 + 5;
int n, k, q;
int lens, lent;
int pos[MAXN];
char s[MAXN], t[MAXN];
char s1[MAXN];
string str[MAXN];
string tt;
string res, res1;
int lens1;
// Templates and namespaces

// Classes

// Funtions
void Print1(int l, int r) {
    for (int i = l; i <= r; i++)
        putchar(t[i]);
}
void Print2(int depth, int l, int r) {
    for (int i = 1; i <= n; i++) {
        if (l < pos[i]) {
            if (r < pos[i]) {
                for (int j = l; j <= r; j++)
                    putchar(s[j]);
                return;
            } else {
                for (int j = l; j < pos[i]; j++)
                    putchar(s[j]);
                l = pos[i];
            }
        }
    }
}

void Pre() {
    for (int i = 1; i <= lens; i++) {
        if (s[i] == '$')
            pos[++n] = i;
    }
}

void Baoli() {
    n = 1;
    for (int i = 1; i <= lent; i++)
        tt = tt + t[i];
    for (int i = 1; i <= lens; i++) {
        if (s[i] != '$')
            str[n] += s[i];
        else
            n++;
    }
    res = tt;
    while (k--) {
        for (int i = 1; i < n; i++)
            res1 = res1 + str[i] + res;
        if (res1.length() >= 1e5)
            break;
        res1 = res1 + str[n];
        res = res1;
        res1 = "";
    }
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--;
        r--;
        for (int i = l; i <= r; i++)
            putchar(res[i]);
        printf("\n");
    }
}

void Baoli1l(int l, int r) {
    int lmod = l % (pos[1] - 1);
    if (lmod == 0)
        lmod = pos[1] - 1;
    int rmod = r % (pos[1] - 1);
    if (rmod == 0)
        rmod = pos[1] - 1;
    if ((rmod - lmod + 1) == (r - l + 1)) {
        for (int i = lmod; i <= rmod; i++)
            putchar(s[i]);
    } else {
        for (int i = lmod; i <= pos[1] - 1; i++)
            putchar(s[i]);
        l += pos[1] - lmod;
        r -= rmod;
        for (int i = l; i <= r; i++)
            putchar(s[i]);
        for (int i = 1; i <= rmod; i++)
            putchar(s[i]);
    }
}
void Baoli1r(int l, int r) {
    int lmod = l % (lens - pos[1]);
    if (lmod == 0)
        lmod = lens - pos[1];
    int rmod = r % (lens - pos[1]);
    if (rmod == 0)
        rmod = (lens - pos[1]);
    if ((rmod - lmod + 1) == (r - l + 1)) {
        for (int i = lmod; i <= rmod; i++)
            putchar(s1[i]);
    } else {
        for (int i = lmod; i <= (lens - pos[1]); i++)
            putchar(s1[i]);
        l += (lens - pos[1]) - lmod + 1;
        r -= rmod;
        for (int i = l; i <= r; i++) {
            int j = i % (lens - pos[1]);
            if (j == 0)
                j = lens - pos[1];
            putchar(s[j]);
        }
        for (int i = 1; i <= rmod; i++)
            putchar(s1[i]);
    }
}
void Baoli1() {
    for (int i = pos[1] + 1; i <= lens; i++)
        s1[i - pos[1]] = s[i];
    int firpt = k * (pos[1] - 1), secpt = firpt + lent;
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        if (l <= firpt) {
            if (r <= firpt)
                Baoli1l(l, r);
            else {
                Baoli1l(l, firpt);
                if (r <= secpt) {
                    for (int i = firpt + 1; i <= r; i++)
                        putchar(t[i - firpt]);
                } else {
                    printf("%s", t);
                    Baoli1r(1, r - secpt);
                }
            }
        } else {
            if (l <= secpt) {
                if (r <= secpt) {
                    for (int i = l; i <= r; i++)
                        putchar(t[i - firpt]);
                } else {
                    for (int i = l; i <= secpt; i++)
                        putchar(t[i - firpt]);
                    Baoli1r(1, r - secpt);
                }
            } else {
                Baoli1r(l - secpt, r - secpt);
            }
        }
    }
}

// Main function
int main() {
    freopen("1715.in", "r", stdin);
    scanf("%s", t + 1);
    lent = strlen(t + 1);
    scanf("%s", s + 1);
    lens = strlen(s + 1);
    scanf("%d%d", &k, &q);
    if (k == 0) {
        while (q--) {
            int l, r;
            scanf("%d%d", &l, &r);
            Print1(l, r);
            printf("\n");
        }
        return 0;
    }
    Pre();
    if (n == 1) {
        std::cout << "a";
        int a;
        Baoli1();
        return 0;
    }
    Baoli();
    // while (q--) {
    //     int l, r;
    //     scanf("%d%d", &l, &r);
    //     // Print2(0, l, r);
    //     printf("\n");
    // }
    return 0;
}