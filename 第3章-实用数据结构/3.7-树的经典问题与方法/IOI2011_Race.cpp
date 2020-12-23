// 例题37  竞赛（Race, IOI 2011，牛客NC51143）
// 求一条简单路径，权值和等于K，且边数最小。
// 陈锋
#include<bits/stdc++.h>
using namespace std;

const int NN = 2e5 + 8, KK = 1e6 + 8, INF = 1 << 30;
int N, K, MaxSub[NN], SZ[NN], F[KK];
// MaxSub[i]: 去除节点i后得到的森林中节点数最多的树的节点
// SZ：保存子树的节点数
// F[i]权值和为i的路径包含的最小边数
bool Vis[NN];
struct Edge { int v, w; };
struct Path { int w, ec; }; // 路径权值之和，边数
vector<Edge> G[NN];

// 获取子树u的重心, treesz为整个子树大小，重心用来更新center
void find_center(int u, int fa, const int treesz, int& center) {
  int &s = SZ[u], &m = MaxSub[u];
  s = 1, m = 0;
  for (const auto &e : G[u]) {
    if (e.v == fa || Vis[e.v]) continue;
    find_center(e.v, u, treesz, center);
    s += SZ[e.v], m = max(m, SZ[e.v]);
  }
  m = max(m, treesz - s);
  if (m < MaxSub[center]) center = u;
}
// 收集子树u中每个点到根节点的路径的{权值和sw,边数ec}，只考虑权值和<=K的
void collect_path(int u, int fa, int sw, int ec, vector<Path> &S) {
  if (sw > K) return;
  S.push_back({sw, ec});
  for (const Edge &e : G[u])
    if (e.v != fa && !Vis[e.v]) collect_path(e.v, u, sw + e.w, ec + 1, S);
}
// 子树u中所有经过u且权值和=K的路径，这些路径长度(边数)的最小值→min_ec
void solve(int u, int& min_ec) {
  vector<int> q;
  for (const auto & e : G[u]) {
    if (Vis[e.v]) continue;
    vector<Path> S;
    collect_path(e.v, u, e.w, 1, S);
    for (auto& it : S) min_ec = min(min_ec, it.ec + F[K - it.w]); // 当前路径和之前子树路径的组合
    for (auto& it : S) q.push_back(it.w), F[it.w] = min(F[it.w], it.ec); // 更新这条路径对应的F值，让后来的子树用
  }
  for (int i : q) F[i] = INF;
}
void dfs(int u, int& min_ec) { // 递归求解子树u
  Vis[u] = true, F[0] = 0;
  solve(u, min_ec); //
  for (const auto & e : G[u]) {
    if (Vis[e.v]) continue;
    int center = 0; // 找子树v的中心，然后递归求解子树v
    find_center(e.v, u, SZ[e.v], center), dfs(center, min_ec);
  }
}

int main() {
  int N;
  scanf("%d%d", &N, &K);
  for (int i = 1, u, v, w; i < N; ++i) {
    scanf("%d%d%d", &u, &v, &w), ++u, ++v;
    G[u].push_back({v, w}), G[v].push_back({u, w});
  }
  fill_n(F, K + 1, INF);
  MaxSub[0] = INF;
  int min_ec = INF, center = 0;
  find_center(1, 0, N, center), dfs(center, min_ec);
  printf("%d\n", min_ec == INF ? -1 : min_ec);
  return 0;
}
// 46224368 Race Accepted 100 643 31840 2091 C++ 2020-12-23 14:23:18