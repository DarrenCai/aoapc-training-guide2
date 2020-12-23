// 例题7  等价性证明（Proving Equivalences, NWERC2008, LA4287/HDU2767）
// 陈锋
#include <bits/stdc++.h>
using namespace std;

const int NN = 20000 + 10;

vector<int> G[NN];
int pre[NN], lowlink[NN], sccno[NN], dfs_clock, scc_cnt;
stack<int> S;
void dfs(int u) {
  int &lu = lowlink[u];
  pre[u] = lu = ++dfs_clock, S.push(u);
  for (size_t i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    if (!pre[v]) dfs(v), lu = min(lu, lowlink[v]);
    else if (!sccno[v]) lu = min(lu, pre[v]);
  }
  if (lu == pre[u]) {
    scc_cnt++;
    for (int x = -1; x != u; S.pop()) x = S.top(), sccno[x] = scc_cnt;
  }
}

void find_scc(int n) {
  dfs_clock = scc_cnt = 0;
  fill_n(sccno, n, 0), fill_n(pre, n, 0);
  for (int i = 0; i < n; i++)
    if (!pre[i]) dfs(i);
}

int in0[NN], out0[NN];
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

    find_scc(n);
    fill_n(in0 + 1, scc_cnt, 1), fill_n(out0 + 1, scc_cnt, 1);
    for (int u = 0; u < n; u++)
      for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (sccno[u] != sccno[v]) in0[sccno[v]] = out0[sccno[u]] = 0;
      }
    int a = 0, b = 0;
    for (int i = 1; i <= scc_cnt; i++) {
      if (in0[i]) a++;
      if (out0[i]) b++;
    }
    int ans = max(a, b);
    if (scc_cnt == 1) ans = 0;
    printf("%d\n", ans);
  }
  return 0;
}
// Accepted 187ms 5424kB 1665 G++2020-12-14 16:11:27 34870207
