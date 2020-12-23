// 例题34  Rikka与路径的交集（Rikka with Intersection of Paths, ACM/ICPC徐州2018, CodeforceGym 102012G）
// 陈锋
#include <bits/stdc++.h>
const int NN = 3e5 + 8, MOD = 1000000007, HH = ceil(log2(NN));
using namespace std;
typedef long long LL;
#define _for(i,a,b) for( int i=(a); i<(int)(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(int)(b); ++i)

void gcd(LL a, LL b, LL& d, LL& x, LL& y) {
  if (!b) d = a, x = 1, y = 0;
  else gcd(b, a % b, d, y, x), y -= x * (a / b);
}
LL inv(LL a, LL n) { // solve ax≡1 mod n
  LL d, x, y;
  gcd(a, n, d, x, y);
  return d == 1 ? (x + n) % n : -1;
}

LL Fact[NN]; // i!
inline LL C(int a, int b) { // C(a, b)
  if (a < 0 || b < 0 || a < b) return 0;
  return 1LL * (Fact[a] * inv(Fact[a - b], MOD) % MOD)
         * inv(Fact[b], MOD) % MOD;
}

vector<int> G[NN];
int Fa[NN][HH + 1], D[NN], P[NN], A[NN];
inline void dfs(int u, int fa, int d) {
  Fa[u][0] = fa, D[u] = d;
  _rep(i, 1, HH) Fa[u][i] = Fa[Fa[u][i - 1]][i - 1];
  for (auto v : G[u]) if (v != fa) dfs(v, u, d + 1);
}

int lca(int u, int v) {
  if (D[u] < D[v]) swap(u, v);
  int diff = D[u] - D[v];
  _rep(h, 0, HH) if (diff & (1 << h)) u = Fa[u][h];
  if (u == v) return u;
  for (int h = HH; h >= 0; h--)
    if (Fa[u][h] != Fa[v][h]) u = Fa[u][h], v = Fa[v][h];
  return Fa[u][0];
}

inline void differ(int u, int fa) { // 树上差分
  for (auto v : G[u])
    if (v != fa) differ(v, u), P[u] += P[v];
}

int main() {
  Fact[0] = 1;
  _for(i, 1, NN) Fact[i] = 1LL * Fact[i - 1] * i % MOD;
  ios::sync_with_stdio(false), cin.tie(0);
  int T; cin >> T;
  for (int t = 0, N, m, k, u, v; t < T; ++t) {
    cin >> N >> m >> k;
    fill_n(P, N + 1, 0), fill_n(A, N + 1, 0);
    _rep(i, 0, N) G[i].clear();
    _for(i, 1, N) cin >> u >> v, G[u].push_back(v), G[v].push_back(u);
    dfs(1, 0, 1);
    for (int i = 1, d; i <= m; ++i) {
      cin >> u >> v, d = lca(u, v);
      ++A[d], ++P[u], ++P[v], --P[d]; // d多计算一次
      if (d != 1) --P[Fa[d][0]]; // Fa[d]-root多计算两次
    } // P[u]: u→根节点路径上点为端点的简单路径条数之和, A[u]: u是几条路径的LCA?
    differ(1, 0); // 树上差分合并之后：P[u]: 有多少条路径经过u
    LL ans = 0; // 对于两条路径的交点，我们只统计是某直线端点LCA的那个，不是LCA的不算
    _rep(i, 1, N) (ans += C(P[i], k) - C(P[i] - A[i], k) + MOD) %= MOD;
    printf("%lld\n", ans);
  }
  return 0;
}
// 72027006 Feb/28/2020 G - Rikka with Intersections of Paths GNU C++11 Accepted  5677 ms 46000 KB