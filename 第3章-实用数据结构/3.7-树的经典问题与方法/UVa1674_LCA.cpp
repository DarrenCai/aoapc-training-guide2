// 例题38 闪电的能量（Lightning Energy Report, ACM/ICPC Jakarta2010, UVa1674）
// 基于LCA的树上差分解法, 陈锋
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50000 + 4;

template <int SZ>
struct LCA {
  vector<int> G[MAXN];
  int N, L, Tin[MAXN], Tout[MAXN], UP[MAXN][18], timer;  // LCA相关
  void init(int _n) {
    N = _n, L = ceil(log2(N)), timer = 0;
    for (int i = 0; i <= N; i++) G[i].clear();
  }
  void addEdge(int u, int v) { G[u].push_back(v), G[v].push_back(u); }
  void dfs(int u, int fa = 0) {
    Tin[u] = ++timer, UP[u][0] = fa;
    for (int i = 1; i <= L; i++) UP[u][i] = UP[UP[u][i - 1]][i - 1];
    for (size_t i = 0; i < G[u].size(); i++)
      if (G[u][i] != fa) dfs(G[u][i], u);
    Tout[u] = ++timer;
  }

  bool isAncestor(int u, int v) { return Tin[u] < Tin[v] && Tout[v] < Tout[u]; }

  int lca(int u, int v) {
    if (u == v) return u;
    if (isAncestor(u, v)) return u;
    if (isAncestor(v, u)) return v;
    for (int i = L; i >= 0; --i)
      if (!isAncestor(UP[u][i], v)) u = UP[u][i];
    return UP[u][0];
  }
};

LCA<MAXN> lca;
int mark[MAXN], ans[MAXN];

int dfs_mark(int u, int fa) {
  int &a = ans[u];
  a = mark[u];
  for (size_t i = 0; i < lca.G[u].size(); i++) {
    int v = lca.G[u][i];
    if (v == fa) continue;
    a += dfs_mark(v, u);
  }
  return a;
}

int main() {
  int T;
  cin >> T;
  for (int kase = 1, N, Q, x, y; kase <= T; kase++) {
    cin >> N, lca.init(N);
    for (int i = 1; i < N; i++) cin >> x >> y, lca.addEdge(x, y);
    lca.dfs(0);
    cin >> Q;
    fill_n(mark, N + 1, 0);
    for (int i = 0, c; i < Q; i++) {
      cin >> x >> y >> c;
      int d = lca.lca(x, y), pd = lca.UP[d][0];
      mark[x] += c, mark[y] += c, mark[d] -= c;
      if (pd != d) mark[pd] -= c;
    }
    dfs_mark(0, 0);
    printf("Case #%d:\n", kase);
    for (int i = 0; i < N; i++) printf("%d\n", ans[i]);
  }
}
// Accepted 130ms 1932 C++5.3.0 2020-12-13 22:25:38 25843936