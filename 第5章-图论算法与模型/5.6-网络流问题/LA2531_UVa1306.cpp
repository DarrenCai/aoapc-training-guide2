// 例题32  足球联赛（The K-league, 大田 2002, LA 2531/UVa1306
// Rujia Liu
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

const int maxn = 700, INF = 1e9;

struct Edge {
  int from, to, cap, flow;
};
bool operator<(const Edge &a, const Edge &b) {
  return a.from < b.from || (a.from == b.from && a.to < b.to);
}
struct Dinic {
  int n, m, s, t;
  vector<Edge> edges; // 边数的两倍
  vector<int> G[maxn]; // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  bool vis[maxn]; // BFS使用
  int d[maxn];    // 从起点到i的距离
  int cur[maxn];  // 当前弧指针

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; i++)
      G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap) {
    edges.push_back((Edge){from, to, cap, 0});
    edges.push_back((Edge){to, from, 0, 0});
    m = edges.size();
    G[from].push_back(m - 2), G[to].push_back(m - 1);
  }

  bool BFS() {
    fill_n(vis, n + 1, false);
    queue<int> Q;
    Q.push(s), vis[s] = true, d[s] = 0;
    while (!Q.empty()) {
      int x = Q.front();
      Q.pop();
      for (size_t i = 0; i < G[x].size(); i++) {
        Edge &e = edges[G[x][i]];
        if (!vis[e.to] && e.cap > e.flow)
          vis[e.to] = true, d[e.to] = d[x] + 1, Q.push(e.to);
      }
    }
    return vis[t];
  }

  int DFS(int x, int a) {
    if (x == t || a == 0)
      return a;
    int flow = 0, f;
    for (int &i = cur[x]; i < G[x].size(); i++) {
      Edge &e = edges[G[x][i]];
      if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
        e.flow += f, edges[G[x][i] ^ 1].flow -= f, flow += f, a -= f;
        if (a == 0)
          break;
      }
    }
    return flow;
  }

  int Maxflow(int s, int t) {
    this->s = s, this->t = t;
    int flow = 0;
    while (BFS())
      fill_n(cur, n + 1, 0), flow += DFS(s, INF);
    return flow;
  }
};
Dinic g;
const int maxt = 25 + 5;
int n, w[maxt], d[maxt], a[maxt][maxt];
inline int ID(int u, int v) { return u * n + v + 1; }
inline int ID(int u) { return n * n + u + 1; }
bool canWin(int team) { // 计算team全胜后的总胜利场数
  int total = w[team] + accumulate(a[team], a[team] + n, 0);
  for (int i = 0; i < n; i++) // 全胜又如何?
    if (w[i] > total)         // 有人已经胜的更多了
      return false;

  // 构图。s=0, 结点(u,v)的编号为u*n+v+1, 结点u的编号为n^2+u+1, t=n^2+n+1
  g.init(n * n + n + 2);
  int full = 0, s = 0, t = n * n + n + 1;
  for (int u = 0; u < n; u++) {
    for (int v = u + 1; v < n; v++) {
      if (a[u][v] > 0)
        g.AddEdge(s, ID(u, v), a[u][v]); // S到(u,v)的弧, 容量是剩余的场次
      full += a[u][v]; // (u,v)到u,v的弧，流量表示胜利属于?
      g.AddEdge(ID(u, v), ID(u), INF), g.AddEdge(ID(u, v), ID(v), INF);
    }
    if (w[u] < total)
      g.AddEdge(ID(u), t, total - w[u]); // u到T的弧，u的只能再胜total-w[u]局
  }
  return g.Maxflow(s, t) == full;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d%d", &w[i], &d[i]);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%d", &a[i][j]);

    for (int i = 0, first = 1; i < n; i++)
      if (canWin(i)) {
        printf("%s", first ? "" : " "), first = 0;
        printf("%d", i+1);
      }
    printf("\n");
  }
  return 0;
}
// 25878256	10779	Collectors Problem	Accepted	C++	0.000	2020-12-23 08:44:16