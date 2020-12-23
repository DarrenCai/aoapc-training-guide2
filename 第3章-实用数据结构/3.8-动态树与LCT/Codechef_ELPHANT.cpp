// 例题44  大象（Elephants, Codechef ELPHANT, IOI 2011 Day 2）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
const int NN = 1e6 + 4;
template<int SZ>
struct LCT {
  int ch[SZ][2], fa[SZ], rev[SZ], val[NN], sum[NN];
  void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = rev[x] = 0; }
  inline int is_right_ch(int x) // x是辅助树上父亲的右儿子?
  { return ch[fa[x]][1] == x; }
  inline int is_root(int x) // x是辅助树根?
  { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
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
  void rotate_up(int x) { // 在辅助树中将x向上旋转一级
    int y = fa[x], z = fa[y], chx = is_right_ch(x), chy = is_right_ch(y),
        &t = ch[x][chx ^ 1]; // t在x,y之间，但是t-x, x-y方向相反
    fa[x] = z;
    if (!is_root(y)) ch[z][chy] = x; // x,y在z的同一侧
    ch[y][chx] = t, fa[t] = y, t = y, fa[y] = x; // 保证t依然在x,y之间
    update_sum(y);
  }
  void splay(int x) {
    pushup(x); // x一直到树根路径上所有点的深度相对关系都要反转
    for (int f = fa[x]; f = fa[x], !is_root(x); rotate_up(x))
      if (!is_root(f)) rotate_up(is_right_ch(x) == is_right_ch(f) ? f : x);
    update_sum(x);
  }
  void access(int x) { // 将root-x变成首选边
    for (int f = 0; x; f = x, x = fa[x])
      splay(x), ch[x][1] = f, update_sum(x);
  }
  void make_root(int x) { access(x), splay(x), swap(ch[x][0], ch[x][1]), rev[x] ^= 1; }
  void split(int x, int y) { make_root(x), access(y), splay(y); }
  int find_root(int x) { // x所在树的树根
    access(x), splay(x);
    while (ch[x][0]) x = ch[x][0];
    splay(x);
    return x;
  }
  void cut(int x, int y) {
    split(x, y);  // x是y在辅助树中的左孩子且要求x,y相邻
    if (ch[y][0] == x && !ch[x][1]) ch[y][0] = fa[x] = 0;
  }
  void link(int x, int y) { if (find_root(x) != find_root(y)) make_root(x), fa[x] = y; }
  void update_sum(int x) { sum[x] = val[x] + sum[ch[x][0]] + sum[ch[x][1]]; }
  int query_sum(int x, int y) { split(x, y); return sum[y]; }
  void modify(int x, int w) { access(x), splay(x), val[x] = w, update_sum(x); }
};
LCT<NN> T;
int N, L, M, P[NN], X[NN], Y[NN], Cnt[NN];
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> N >> L >> M;
  vector<int> ps;
  ps.push_back(-1), ps.push_back(2e9);
  for (int i = 1; i <= N; i++)
    cin >> P[i], ps.push_back(P[i]), ps.push_back(P[i] + L + 1);
  for (int i = 1; i <= M; i++) {
    cin >> X[i] >> Y[i], X[i]++;
    ps.push_back(Y[i]), ps.push_back(Y[i] + L + 1);
  } // 记录所有可能的点的位置
  sort(ps.begin(), ps.end()), ps.erase(unique(ps.begin(), ps.end()), ps.end());
  int sz = ps.size();
  unordered_map<int, int> PLoc;
  for (int i = 0; i < sz; i++) PLoc[ps[i]] = i; // 离散化

  for (int i = 2; i <= sz; i++) T.link(i - 1, i);
  for (int i = 1; i <= N; i++) { // 所有大象
    int u = PLoc[P[i]]; // u是在i位置上的大象
    if (!Cnt[u]) T.cut(u, u + 1), T.link(u, PLoc[P[i] + L + 1]), T.modify(u, 1);
    Cnt[u]++; // 大象节点p只和p+L+1相连
  }

  for (int i = 1; i <= M; i++) {
    int &px = P[X[i]], y = Y[i], ou = PLoc[px], u = PLoc[y];
    if (--Cnt[ou] == 0) // ou不再是大象了
      T.cut(ou, PLoc[px + L + 1]), T.link(ou, ou + 1), T.modify(ou, 0);
    if (Cnt[u]++ == 0) // u变成大象了
      T.cut(u, u + 1), T.link(u, PLoc[y + L + 1]), T.modify(u, 1);
    px = y;
    cout << T.query_sum(1, sz) << endl;
  }
  return 0;
}
// 64389  1 min ago sukhoeing 100[1pts]  1.10  90.1M C++14