// 例题48 金币（Coins, ACM/ICPC Asia – Amritapuri 2015，Codechef AMCOINS）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
template <int SZ>
struct BIT {
  int C[SZ], sz;
  void init(int _sz) {
    sz = _sz;
    assert(sz + 1 < SZ);
  }
  inline int lowbit(int x) { return x & -x; }
  void add(int x, int y) {
    while (x < SZ) C[x] += y, x += lowbit(x);
  }
  int sum(int x) {
    int s = 0;
    while (x > 0) s += C[x], x -= lowbit(x);
    return s;
  }
};
const int NN = 5e5 + 8, QQ = 1e5 + 8, HH = 20;
vector<int> G[NN];
struct Cmd {
  int op, x, y, w, z, k, id, time;
  friend bool operator<(const Cmd& a, const Cmd& b) {
    if (a.time != b.time) return a.time < b.time;
    return a.op < b.op;
  }
};
int Tin[NN], Tout[NN], Dfn, Fa[NN][HH + 1], Dep[NN];  // DFS, LCA
int lca(int u, int v) {
  if (Dep[u] < Dep[v]) swap(u, v);
  int d = Dep[u] - Dep[v];
  for (int h = 0; h <= HH; h++)
    if (d & (1 << h)) u = Fa[u][h];
  if (u == v) return u;
  for (int h = HH; h >= 0; h--)
    if (Fa[u][h] != Fa[v][h]) u = Fa[u][h], v = Fa[v][h];
  return Fa[u][0];
}
void dfs(int u, int fa) {  // Tin[u]:先序遍历序列中的编号，
  Tin[u] = ++Dfn, Fa[u][0] = fa, Dep[u] = Dep[fa] + 1;
  for (int h = 1; h <= HH; h++) Fa[u][h] = Fa[Fa[u][h - 1]][h - 1];
  for (auto v : G[u])
    if (fa != v) dfs(v, u);
  Tout[u] = Dfn;  // Tin[u]-Tout[u]: u子树先序遍历序列中的区间
}
BIT<NN> S;
int Cnt[QQ], Ans[QQ];
void apply(const Cmd& q, bool rev = false) {
  int d = lca(q.x, q.y), c = rev ? -1 : 1;  // x-y路径上全部增加一个计数
  S.add(Tin[q.x], c), S.add(Tin[q.y], c),
      S.add(Tin[d], -c);                 // +(x-root), +(y-root), -(d-root)
  if (d != 1) S.add(Tin[Fa[d][0]], -c);  // d != root, -(fa(d)-root)
}
void solve(int al, int ar,
           const vector<Cmd>& qs) {  // Qs[ql,qr]的答案都在[al, ar]中
  if (qs.empty()) return;
  int am = (al + ar) / 2;
  vector<Cmd> B;
  for (const auto& q : qs) {
    if (q.op == 1) {                  // 修改操作
      if (q.w <= am) B.push_back(q);  // 增加一个[al, am]中的Coin
    } else {  // query[]，拆成对两个时间段的查询:[1,I-1],[1,J],结果考虑正负
      B.push_back(q), B.back().time = q.x - 1, B.back().w = -1;
      B.push_back(q), B.back().time = q.y, B.back().w = 1;
      Cnt[q.id] = 0;  // [al,am]中的操作在q.z节点增加了几个硬币
    }
  }
  sort(begin(B), end(B));  // 时间排序，相同时间: 写在读前
  for (const Cmd& q : B) {
    if (q.op == 1)
      apply(q);  // 修改操作，树上差分
    else  // 版本[1,J]增加的[al,am]中的硬币数量-[1,I-1]增加的[al,am]中的
      Cnt[q.id] += q.w * (S.sum(Tout[q.z]) - S.sum(Tin[q.z] - 1));
  }
  for (const Cmd& q : B)
    if (q.op == 1) apply(q, true);  // 还原所有修改操作

  if (al == ar) {  // 答案已经锁定
    for (auto& q : qs)
      if (q.op == 2 && Cnt[q.id] >= q.k) Ans[q.id] = al;
    return;
  }
  vector<Cmd> lqs, rqs;
  for (auto& q : qs) {
    if (q.op == 1) {
      if (q.w <= am)
        lqs.push_back(q);  // 拆入一个[al,am]中的硬币
      else
        rqs.push_back(q);  // 插入一个[am+1,ar]中的
    } else {
      if (Cnt[q.id] >= q.k)
        lqs.push_back(q);  // 答案在[al,am]中的查询
      else
        rqs.push_back(q), rqs.back().k -= Cnt[q.id];  // 答案在[am+1,ar]中的查询
    }
  }
  solve(al, am, lqs), solve(am + 1, ar, rqs);
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int n, m, qc = 0;
  cin >> n;
  for (int i = 1, x, y; i < n; i++)
    cin >> x >> y, G[x].push_back(y), G[y].push_back(x);
  Dfn = 0, dfs(1, 0);
  cin >> m;
  vector<Cmd> Qs(m);
  for (int i = 1; i <= m; i++) {
    Cmd& q = Qs[i - 1];
    cin >> q.op;
    if (q.op == 1)
      cin >> q.x >> q.y >> q.w, q.time = i;
    else
      cin >> q.z >> q.x >> q.y >> q.k, q.id = ++qc;
  }
  solve(1, 100000, Qs);
  for (int i = 1; i <= qc; i++) printf("%d\n", Ans[i] ? Ans[i] : -1);
  return 0;
}
// 30222279 05:42 PM 09/03/20 sukhoeing   0.96  116.4M  C++14