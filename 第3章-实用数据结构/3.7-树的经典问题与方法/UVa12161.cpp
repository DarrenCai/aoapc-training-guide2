// 例题36  铁人比赛（Ironman Race in Treeland, ACM/ICPC Kuala Lumpur 2008, UVa12161）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Edge { int v, d, l; };
const int INF = 0x3f3f3f3f, MAXN = 3e4 + 10;
typedef map<int, int>::iterator MIT;

int N, M, MaxSub[MAXN], SZ[MAXN], VIS[MAXN], Dep[MAXN], Cost[MAXN];
// MaxSub[i]: 去除节点i后得到的森林中节点数最多的树的节点, SZ[u]：子树u的体积,
// Dep:长度，Cost: 路径的费用
vector<Edge> G[MAXN];
void find_center(int u, int fa, const int tree_sz, int& center) {  //找重心
  int &szu = SZ[u], &msu = MaxSub[u];
  szu = 1, msu = 0;
  for (const Edge& e : G[u]) {
    if (e.v == fa || VIS[e.v]) continue;
    find_center(e.v, u, tree_sz, center);
    szu += SZ[e.v], msu = max(msu, SZ[e.v]);
  }
  msu = max(msu, tree_sz - SZ[u]);
  if (MaxSub[center] > msu) center = u;
}

void insert_cd(map<int, int>& ps, int c, int d) {
  if (c > M) return;
  MIT it = ps.upper_bound(c);
  if (it == ps.begin() || (--it)->second < d) {  // 保证ps里面{费用:长度}同时递增
    ps[c] = d;               // (it-1)->c≤c，要求d>(it-1)->d才插入c:d
    it = ps.upper_bound(c);  // 对于所有的 it(it->c>c)，要求it->d>d，否则删除
    while (it != ps.end() && it->second <= d) ps.erase(it++);
  }
}

void collect_deps(int u, int fa, map<int, int>& ps) {  // 子树u节点路径的花费:长度
  SZ[u] = 1;
  insert_cd(ps, Cost[u], Dep[u]);
  for (const Edge& e : G[u]) {
    if (e.v == fa || VIS[e.v]) continue;
    Dep[e.v] = Dep[u] + e.l, Cost[e.v] = Cost[u] + e.d;
    collect_deps(e.v, u, ps), SZ[u] += SZ[e.v];
  }
}

void count(int u, int& max_len) {  // 计算经过子树u根结点的路径数
  map<int, int> ps, vps;           // u子树, v子树中的 费用:长度
  ps[0] = 0;
  for (const Edge& e : G[u]) {
    if (VIS[e.v]) continue;
    Dep[e.v] = e.l, Cost[e.v] = e.d;
    vps.clear(), collect_deps(e.v, u, vps);
    for (const pair<int, int>& p : vps) {
      MIT it = ps.upper_bound(M - p.first);
      if (it != ps.begin()) max_len = max(max_len, p.second + (--it)->second);
    }
    for (const pair<int, int>& p : vps) insert_cd(ps, p.first, p.second);
  }
}

void solve(int u, int& max_len) {
  count(u, max_len), VIS[u] = true;
  for (const Edge& e : G[u]) {
    if (VIS[e.v]) continue;
    int center = 0;
    find_center(e.v, u, SZ[e.v], center), solve(center, max_len);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int kase = 1; kase <= T; kase++) {
    scanf("%d%d", &N, &M);
    fill_n(VIS, N + 1, 0), MaxSub[0] = N;
    for (int i = 1; i <= N; i++) G[i].clear();
    for (int i = 1, u, v, d, l; i < N; i++) {
      scanf("%d%d%d%d", &u, &v, &d, &l);
      G[u].push_back({v, d, l}), G[v].push_back({u, d, l});
    }
    int center = 0, max_len = 0;
    find_center(1, -1, N, center);  // 找到初始的重心
    solve(center, max_len);         // 递归求解
    printf("Case %d: %d\n", kase, max_len);
  }
  return 0;
}
// Accepted 210ms 2797 C++ 5.3.0 2020-12-13 22:11:33 25843886