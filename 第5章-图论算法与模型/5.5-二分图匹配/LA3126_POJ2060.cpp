// 例题29  出租车（Taxi Cab Scheme, NWERC 2004, LA 3126/POJ2060
// 陈锋
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500 + 5;  // 单侧顶点的最大数目

// 二分图最大基数匹配，邻接矩阵写法
struct BPM {
  int n, m;           // 左右顶点个数
  int G[maxn][maxn];  // 邻接表
  int left[maxn];  // left[i]为右边第i个点的匹配点编号，-1表示不存在
  bool T[maxn];  // T[i]为右边第i个点是否已标记

  void init(int n, int m) {
    this->n = n, this->m = m;
    memset(G, 0, sizeof(G));
  }

  bool match(int u) {
    for (int v = 0; v < m; v++)
      if (G[u][v] && !T[v]) {
        T[v] = true;
        if (left[v] == -1 || match(left[v])) {
          left[v] = u;
          return true;
        }
      }
    return false;
  }

  // 求最大匹配
  int solve() {
    fill_n(left, m + 1, -1);
    int ans = 0;
    for (int u = 0; u < n; u++) {  // 从左边结点u开始增广
      fill_n(T, m + 1, false);
      if (match(u)) ans++;
    }
    return ans;
  }
};

BPM solver;
int X1[maxn], Y1[maxn], X2[maxn], Y2[maxn], T1[maxn], T2[maxn];
inline int dist(int a, int b, int c, int d) { return abs(a - c) + abs(b - d); }

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 0, n; t < T; t++) {
    scanf("%d", &n);
    for (int i = 0, h, m; i < n; i++) {
      scanf("%d:%d%d%d%d%d", &h, &m, &X1[i], &Y1[i], &X2[i], &Y2[i]);
      T1[i] = h * 60 + m, T2[i] = T1[i] + dist(X1[i], Y1[i], X2[i], Y2[i]);
    }
    solver.init(n, n);
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if (T2[i] + dist(X2[i], Y2[i], X1[j], Y1[j]) < T1[j])
          solver.G[i][j] = 1;  // 至少要提前1分钟到达
    printf("%d\n", n - solver.solve());
  }
  return 0;
}
// Accepted 188ms 1332kB 1704 G++2020-12-14 18:19:37 22209579