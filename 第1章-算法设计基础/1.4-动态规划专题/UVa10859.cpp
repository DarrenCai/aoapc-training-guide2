// 例题30  放置街灯（Placing Lampposts, UVa 10859）
// 陈锋
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int NN = 1000 + 8, BASE = 2000;
vector<int> G[NN];  // 森林是稀疏的，这样保存省空间，枚举相邻结点也更快
int Vis[NN][2], D[NN][2], N, M;

int dp(int i, int j, int f) {  // DFS的同时进行动态规划,f是父结点, 不存入状态里
  if (Vis[i][j]) return D[i][j];
  Vis[i][j] = 1;
  int& ans = D[i][j];

  // 放灯总是合法决策
  ans = BASE;  // 灯的数量加1，x加BASE
  for (int k = 0; k < G[i].size(); k++)
    if (G[i][k] != f)  // 这个判断非常重要！除了父结点之外的相邻结点才是子结点
      ans += dp(G[i][k], 1, i);  // 注意，这些结点的父结点是i
  if (!j && f >= 0) ans++;  // 如果i不是根，且父结点没放灯，则x加1

  if (j || f < 0) {  // i是根或者其父结点已放灯，i才可以不放灯
    int sum = 0;
    for (int k = 0; k < G[i].size(); k++)
      if (G[i][k] != f) sum += dp(G[i][k], 0, i);
    if (f >= 0) sum++;  // 如果i不是根，则x加1
    ans = min(ans, sum);
  }
  return ans;
}

int main() {
  int T, a, b;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) G[i].clear();
    for (int i = 0, a, b; i < M; i++)
      scanf("%d%d", &a, &b), G[a].push_back(b), G[b].push_back(a);
    memset(Vis, 0, sizeof(Vis));
    int ans = 0;
    for (int i = 0; i < N; i++)
      if (!Vis[i][0]) ans += dp(i, 0, -1);  // 新的一棵树的树根
    printf("%d %d %d\n", ans/BASE, M - ans%BASE, ans%BASE);  //从x计算3个整数
  }
  return 0;
}
// Accepted 1365 C++5.3.0 2020-12-08 21:06:32 25825938