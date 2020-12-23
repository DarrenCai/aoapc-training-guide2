// 例题57  自带版本控制功能的IDE（Version Controlled IDE, ACM/ICPC Hatyai 2012, UVa12538）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
#define _for(i, a, b) for (decltype(b) i = (a); i < (b); ++i)
const int MAXN = (1 << 23), MAXQ = 50000 + 4;
struct Node;
typedef Node *PNode;
PNode Null, VER[MAXQ];
struct Node {
  PNode left, right;
  char label;  // user def label
  int key, sz;
  Node(char c = 0, int s = 1) : label(c), sz(s) {
    left = right = Null, key = rand();
  }
  PNode update() {
    sz = 1 + left->sz + right->sz;
    return this;
  }
};
Node Nodes[MAXN];
struct Treap {
  int bufIdx = 0, d;  // this problem need.
  PNode copyOf(PNode u) {
    if (u == Null) return u;
    PNode ret = &Nodes[bufIdx++];
    *ret = *u;
    return ret;
  }
  PNode merge(PNode a, PNode b) {
    if (a == Null) return copyOf(b);
    if (b == Null) return copyOf(a);
    PNode ret;
    if (a->key < b->key)
      ret = copyOf(a), ret->right = merge(a->right, b);
    else
      ret = copyOf(b), ret->left = merge(a, b->left);
    return ret->update();
  }
  void split(PNode pn, PNode &l, PNode &r, const int k) {
    int psz = pn->sz, plsz = pn->left->sz;
    if (k == 0)
      l = Null, r = copyOf(pn);
    else if (psz <= k)
      l = copyOf(pn), r = Null;
    else if (plsz >= k)
      r = copyOf(pn), split(pn->left, l, r->left, k), r->update();
    else
      l = copyOf(pn), split(pn->right, l->right, r, k - plsz - 1), l->update();
  }

  PNode build(int l, int r, const char *s) {
    if (l > r) return Null;
    int m = (l + r) / 2;
    Node u(s[m]);
    PNode a = copyOf(&u), p = build(l, m - 1, s), q = build(m + 1, r, s);
    p = merge(p, a), a = merge(p, q);
    return a->update();
  }
  PNode insert(const PNode ver, int pos, const char *s) {
    PNode p, q, r = build(0, strlen(s) - 1, s);
    split(ver, p, q, pos);
    return merge(merge(p, r), q);
  }
  PNode remove(PNode ver, int pos, int n) {
    PNode p, q, r;
    split(ver, p, q, pos - 1), split(q, q, r, n);
    return merge(p, r);
  }
  void print(PNode ver) {
    if (ver == Null) return;
    print(ver->left), d += (ver->label == 'c');
    putchar(ver->label);
    print(ver->right);
  }
  void debugPrint(PNode pn) {
    if (pn == Null) return;
    debugPrint(pn->left), putchar(pn->label), debugPrint(pn->right);
  }
  void traversal(PNode pn, int pos, int n) {
    PNode p, q, r;
    split(pn, p, q, pos - 1), split(q, q, r, n), print(q);
  }
  void init() { bufIdx = 0, d = 0, Null = &Nodes[bufIdx++], Null->sz = 0; }
};
Treap tree;
int main() {
  int n, opt, v, p, c, ver = 0;
  scanf("%d", &n), tree.init();
  char s[128];
  VER[0] = Null;
  _for(i, 0, n) {
    scanf("%d", &opt);
    switch (opt) {
      case 1:
        scanf("%d %s", &p, s), p -= tree.d;
        VER[ver + 1] = tree.insert(VER[ver], p, s), ver++;
        break;
      case 2:
        scanf("%d %d", &p, &c), p -= tree.d, c -= tree.d;
        VER[ver + 1] = tree.remove(VER[ver], p, c), ver++;
        break;
      case 3:
        scanf("%d%d%d", &v, &p, &c), v -= tree.d, p -= tree.d, c -= tree.d;
        tree.traversal(VER[v], p, c), puts("");
        break;
      default:
        break;
    }
  }
  return 0;
}
// Accepted 280ms 3205 C++5.3.0 2020-12-13 23:23:21 25844155