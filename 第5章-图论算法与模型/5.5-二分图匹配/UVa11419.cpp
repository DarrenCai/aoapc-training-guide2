// 例题27  我是SAM（SAM I AM, UVa 11419）
// 陈锋
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 1000 + 5;  // 单侧顶点的最大数目

// 二分图最大基数匹配
struct BPM {
  int n, m;             // 左右顶点个数
  vector<int> G[maxn];  // 邻接表
  int left[maxn];  // left[i]为右边第i个点的匹配点编号，-1表示不存在
  bool T[maxn];  // T[i]为右边第i个点是否已标记

  int right[maxn];  // 求最小覆盖用
  bool S[maxn];     // 求最小覆盖用

  void init(int n, int m) {
    this->n = n, this->m = m;
    for (int i = 0; i < n; i++) G[i].clear();
  }

  void AddEdge(int u, int v) { G[u].push_back(v); }

  bool match(int u) {
    S[u] = true;
    for (size_t i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
      if (!T[v]) {
        T[v] = true;
        if (left[v] == -1 || match(left[v])) {
          left[v] = u, right[u] = v;
          return true;
        }
      }
    }
    return false;
  }

  // 求最大匹配
  int solve() {
    fill_n(left, m + 1, -1), fill_n(right, n + 1, -1);
    int ans = 0;
    for (int u = 0; u < n; u++) {  // 从左边结点u开始增广
      fill_n(S, n + 1, false), fill_n(T, m + 1, false);
      if (match(u)) ans++;
    }
    return ans;
  }

  // 求最小覆盖。X和Y为最小覆盖中的点集
  int mincover(vector<int>& X, vector<int>& Y) {
    int ans = solve();
    fill_n(S, n + 1, false), fill_n(T, m + 1, false);
    for (int u = 0; u < n; u++) if (right[u] == -1) match(u); // 从所有X未盖点出发增广
    for (int u = 0; u < n; u++) if (!S[u]) X.push_back(u); // X中的未标记点
    for (int v = 0; v < m; v++) if (T[v]) Y.push_back(v); // Y中的已标记点
    return ans;
  }
};

BPM solver;
int main() {
  for (int R, C, N; scanf("%d%d%d", &R, &C, &N) == 3 && R && C && N;) {
    solver.init(R, C);
    for (int i = 0, r, c; i < N; i++)
      scanf("%d%d", &r, &c), r--, c--, solver.AddEdge(r, c);
    vector<int> X, Y;
    int ans = solver.mincover(X, Y);
    printf("%d", ans);
    for (size_t i = 0; i < X.size(); i++) printf(" r%d", X[i] + 1);
    for (size_t i = 0; i < Y.size(); i++) printf(" c%d", Y[i] + 1);
    printf("\n");
  }
  return 0;
}
// Accepted 20ms 2047 C++5.3.0 2020-12-14 18:14:53 25846729