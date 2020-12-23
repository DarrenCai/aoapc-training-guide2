// 例题15  在环中（Going in Cycle!!, UVa 11090）
// 陈锋
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int INF = 1e9, NN = 1000;

struct Edge {
  int from, to;
  double dist;
};

struct BellmanFord {
  int n, m;
  vector<Edge> edges;
  vector<int> G[NN];
  bool inq[NN];     // 是否在队列中
  double d[NN];     // s到各个点的距离
  int p[NN];        // 最短路中的上一条弧
  int cnt[NN];      // 进队次数

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, double dist) {
    edges.push_back((Edge) {from, to, dist});
    m = edges.size();
    G[from].push_back(m - 1);
  }

  bool negativeCycle() {
    queue<int> Q;
    memset(inq, 0, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) { d[i] = 0; inq[0] = true; Q.push(i); }

    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = false;
      for (int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if (d[e.to] > d[u] + e.dist) {
          d[e.to] = d[u] + e.dist;
          p[e.to] = G[u][i];
          if (!inq[e.to]) { Q.push(e.to); inq[e.to] = true; if (++cnt[e.to] > n) return true; }
        }
      }
    }
    return false;
  }
};

BellmanFord solver;
bool test(double x) {
  for (int i = 0; i < solver.m; i++)
    solver.edges[i].dist -= x;
  bool ret = solver.negativeCycle();
  for (int i = 0; i < solver.m; i++)
    solver.edges[i].dist += x;
  return ret;
}

int main() {
  int T; scanf("%d", &T);
  for (int kase = 1, n, m; scanf("%d%d", &n, &m), kase <= T; kase++) {
    solver.init(n);
    int ub = 0;
    for (int i = 0, u, v, w; i < m; i++) {
      scanf("%d%d%d", &u, &v, &w), u--, v--, ub = max(ub, w);
      solver.AddEdge(u, v, w);
    }
    printf("Case #%d: ", kase);
    if (!test(ub + 1)) printf("No cycle found.\n");
    else {
      double L = 0, R = ub;
      while (R - L > 1e-3) {
        double M = L + (R - L) / 2;
        if (test(M)) R = M; else L = M;
      }
      printf("%.2lf\n", L);
    }
  }
  return 0;
}
// Accepted 50ms 2056 C++11 5.3.0 2020-01-31 17:59:48 24490896