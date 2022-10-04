// 例题15  网络（Network, Seoul 2007,UVa1267）
// Rujia Liu
#include <bits/stdc++.h>
using namespace std;
const int NN = 1000 + 4;
vector<int> G[NN], nodes[NN];
int N, S, K, fa[NN];
bool covered[NN];
// 无根树转有根树，计算fa数组，根据深度把叶子结点插入nodes表里
void dfs(int u, int f, int d) {
  fa[u] = f;
  if (G[u].size() == 1 && d > K)
    nodes[d].push_back(u);
  for (int v : G[u])
    if (v != f)
      dfs(v, u, d + 1);
}
void dfs2(int u, int f, int d) {
  covered[u] = true;
  for (int v : G[u])
    if (v != f && d < K) // 只覆盖到新服务器距离不超过k的结点
      dfs2(v, u, d + 1); 
}
int solve() {
  int ans = 0;
  fill_n(covered, N+1, 0);
  for (int d = N - 1; d > K; d--)
    for(int u : nodes[d]){
      if (covered[u]) continue; // 不考虑已覆盖的结点
      int v = u;
      for (int j = 0; j < K; j++) v = fa[v];    // v是u的k级祖先
      dfs2(v, -1, 0), ans++; // 在结点v放服务器
    }
  return ans;
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> N >> S >> K;
    for (int i = 1; i <= N; i++)
      G[i].clear(), nodes[i].clear();
    for (int i = 0, a, b; i < N - 1; i++)
      cin>>a>>b, G[a].push_back(b), G[b].push_back(a);
    dfs(S, -1, 0);
    printf("%d\n", solve());
  }
  return 0;
}
// 25875799	1267	Network	Accepted	C++	0.000	2020-12-22 14:36:36
