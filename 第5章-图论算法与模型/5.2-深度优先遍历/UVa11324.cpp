// 例题8  最大团（The Largest Clique, UVa 11324）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
const int NN = 1000 + 10;
vector<int> G[NN];
int pre[NN], lowlink[NN], sccno[NN], dfs_clock, scc_cnt;
stack<int> S;
void dfs(int u) {
  int& lu = lowlink[u];
  pre[u] = lu = ++dfs_clock, S.push(u);
  for (size_t i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    if (!pre[v])
      dfs(v), lu = min(lu, lowlink[v]);
    else if (!sccno[v])
      lu = min(lu, pre[v]);
  }
  if (lu == pre[u]) {
    scc_cnt++;
    for (int x = -1; x != u; S.pop()) sccno[x = S.top()] = scc_cnt;
  }
}

void find_scc(int n) {
  dfs_clock = scc_cnt = 0;
  fill_n(sccno, n, 0), fill_n(pre, n, 0);
  for (int i = 0; i < n; i++)
    if (!pre[i]) dfs(i);
}

int SccSz[NN], TG[NN][NN], D[NN];
int dp(int u) {
  int& ans = D[u];
  if (ans >= 0) return ans;
  ans = SccSz[u];
  for (int v = 1; v <= scc_cnt; v++)
    if (u != v && TG[u][v]) ans = max(ans, dp(v) + SccSz[u]);
  return ans;
}

int main() {
  int T, n, m;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) G[i].clear();
    for (int i = 0, u, v; i < m; i++) {
      scanf("%d%d", &u, &v), u--, v--;
      G[u].push_back(v);
    }

    find_scc(n);  // 找强连通分量
    memset(TG, 0, sizeof(TG));
    memset(SccSz, 0, sizeof(SccSz));
    for (int i = 0; i < n; i++) {
      SccSz[sccno[i]]++;  // 累加强连通分量大小（结点数）
      for (size_t j = 0; j < G[i].size(); j++)
        TG[sccno[i]][sccno[G[i][j]]] = 1;  // 构造SCC图
    }

    int ans = 0;
    memset(D, -1, sizeof(D));           // 初始化动态规划记忆化数组
    for (int i = 1; i <= scc_cnt; i++)  // 注意，SCC编号为1~scc_cnt
      ans = max(ans, dp(i));
    printf("%d\n", ans);
  }
  return 0;
}
// Accepted 80ms 1740 C++5.3.0 2020-12-14 16:16:29 25846267