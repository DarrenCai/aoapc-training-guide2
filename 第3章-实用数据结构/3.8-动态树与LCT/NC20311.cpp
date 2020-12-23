// NC20311 例题41  洞穴勘测（Cave, SDOI2008）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
const int NN = 1e5 + 4;
template <int SZ>
struct LCT {
  int ch[SZ][2], fa[SZ], rev[SZ];
  void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = rev[x] = 0; }
  // x是辅助树上父亲的右儿子?
  inline int is_right_ch(int x) { return ch[fa[x]][1] == x; }
  // x是辅助树根?
  inline int is_root(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
  void pushdown(int x) {
    if (rev[x] == 0) return;
    int lx = ch[x][0], rx = ch[x][1];
    if (lx) swap(ch[lx][0], ch[lx][1]), rev[lx] ^= 1;
    if (rx) swap(ch[rx][0], ch[rx][1]), rev[rx] ^= 1;
    rev[x] = 0;
  }
  void pushup(int x) {
    if (!is_root(x)) pushup(fa[x]);
    pushdown(x);
  }
  void rotate_up(int x) {  // 将x向上旋转一级
    int y = fa[x], z = fa[y], chx = is_right_ch(x), chy = is_right_ch(y),
        &t = ch[x][chx ^ 1];  // t在x,y之间，但是t-x, x-y方向相反
    fa[x] = z;
    if (!is_root(y)) ch[z][chy] = x;              // x,y在z的同一侧
    ch[y][chx] = t, fa[t] = y, t = y, fa[y] = x;  // 保证t依然在x,y之间
  }
  void splay(int x) {
    pushup(x);  // x一直到树根路径上所有点的深度相对关系都要反转
    for (int f = fa[x]; f = fa[x], !is_root(x); rotate_up(x))
      if (!is_root(f)) rotate_up(is_right_ch(x) == is_right_ch(f) ? f : x);
  }
  void access(int x) {  // 将root-x变成首选边
    for (int f = 0; x; f = x, x = fa[x]) splay(x), ch[x][1] = f;
  }
  void make_root(int x) {  // 将x变为树根
    access(x), splay(x), swap(ch[x][0], ch[x][1]), rev[x] ^= 1;
  }
  void split(int x, int y) { make_root(x), access(y), splay(y); }
  int find_root(int x) {  // x所在树的树根
    access(x), splay(x);
    while (ch[x][0]) x = ch[x][0];
    splay(x);
    return x;
  }
  void cut(int x, int y) {
    split(x, y);  // x是y在辅助树中的左孩子且要求x,y相邻
    if (ch[y][0] == x && !ch[x][1]) ch[y][0] = fa[x] = 0;
  }

  void link(int x, int y) {
    if (find_root(x) != find_root(y)) make_root(x), fa[x] = y;
  }
};
LCT<NN> st;
int main() {
  int n, q, x, y;
  char op[16];
  scanf("%d%d", &n, &q);
  while (q--) {
    scanf("%s%d%d", op, &x, &y);
    switch (op[0]) {
      case 'Q':
        puts(st.find_root(x) == st.find_root(y) ? "Yes" : "No");
        break;
      case 'C':
        st.link(x, y);
        break;
      case 'D':
        st.cut(x, y);
        break;
      default:
        break;
    }
  }
  return 0;
}
// 46047349 [SDOI2008]CAVE 洞穴勘测 AC 100 176 632 2234 C++ 2020-12-13 22:37:56