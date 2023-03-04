// Statement and information
/*
    Author: Conless
    Date: 2022-10-05
    File name: /oi/acmoj/1686_1.cpp
*/

// Headers
#include <bits/stdc++.h>

// Constants, global variables and definitions

typedef long long ll;

const int MAXN = 1e6 + 5;
int n, m;
char s[MAXN];

// Templates and namespaces
namespace Template {
class QuickRead {

public:
  inline char gc() {
    static const int IN_LEN = 1 << 18 | 1;
    static char buf[IN_LEN], *s, *t;
    return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)),
           s == t ? -1 : *s++;
  }

  template <typename _Tp> inline QuickRead &operator>>(_Tp &num) {
    static char ch, sgn;
    ch = gc();
    sgn = 0;
    for (; !isdigit(ch); ch = gc()) {
      if (ch == -1)
        return *this;
      sgn |= (ch == '-');
    }
    num = 0;
    for (num = 0; isdigit(ch); ch = gc())
      num = num * 10 + (ch ^ '0');
    sgn && (num = -num);
    return *this;
  }
} qin;
class SegmentTree {
  /*
      Template name: The template of binary indexed tree, single edit and range
     query Author: Conless Date: 2017-11-15 File name: /oi/template/bitree.hpp
      Required constants: MAXN (the size of the tree)
  */

  struct TreeNode {
    int l, r, mid;
    int lson, rson, tag;
    ll cnt, sum, tot;
  } segTree[MAXN << 2];

#define sn segTree[node]
#define sl segTree[sn.lson]
#define sr segTree[sn.rson]
#define troot segTree[1]

public:
  void pushup(int node) {
    sn.cnt = sl.cnt + sr.cnt;
    sn.sum = sl.sum + sr.sum;
    sn.tot = sl.tot + sr.tot;
  }
  void build(int node, int l, int r) {
    sn.l = l;
    sn.r = r;
    sn.mid = (l + r) >> 1;
    if (l == r) {
      sn.cnt = (s[l] == '0');
      sn.sum = sn.cnt * l;
      sn.tot = l;
      return;
    }
    sn.lson = node << 1;
    sn.rson = node << 1 | 1;
    build(sn.lson, l, sn.mid);
    build(sn.rson, sn.mid + 1, r);
    pushup(node);
  }
  void pushdown(int node) {
    if (!sn.tag)
      return;
    sl.cnt = sn.mid - sn.l + 1 - sl.cnt;
    sr.cnt = sn.r - (sn.mid + 1) + 1 - sr.cnt;
    sl.sum = sl.tot - sl.sum;
    sr.sum = sr.tot - sr.sum;
    sl.tag ^= 1;
    sr.tag ^= 1;
    sn.tag = 0;
  }
  void update(int node, int left, int right) {
    pushdown(node);
    if (left > sn.r || right < sn.l)
      return;
    if (left <= sn.l && right >= sn.r) {
      sn.tag ^= 1;
      sn.cnt = sn.r - sn.l + 1 - sn.cnt;
      sn.sum = sn.tot - sn.sum;
      return;
    }
    update(sn.lson, left, right);
    update(sn.rson, left, right);
    pushup(node);
  }
  ll query() { return (troot.sum << 1) - (troot.cnt * troot.cnt); }
};
}

using Template::qin;
using Template::SegmentTree;

SegmentTree stree;

// Classes

// Funtions

// Main function
int main() {
  scanf("%d%d", &n, &m);
  scanf("%s", s + 1);
  stree.build(1, 1, n);
  printf("%lld\n", stree.query());
  while (m--) {
    int l, r;
    qin >> l >> r;
    stree.update(1, l, r);
    printf("%lld\n", stree.query());
  }
  return 0;
}