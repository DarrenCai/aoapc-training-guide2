// 例题30  UVa11248 Frequency Hopping：使用ISAP算法，加优化
// 刘汝佳
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int NN = 100 + 10, INF = 1e9;
struct Edge {
  int from, to, cap, flow;
};
bool operator<(const Edge &a, const Edge &b) {
  return a.from < b.from || (a.from == b.from && a.to < b.to);
}
struct ISAP {
  int n, m, s, t;
  vector<Edge> edges;
  vector<int> G[NN]; // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  bool vis[NN]; // BFS使用
  int d[NN];    // 从起点到i的距离
  int cur[NN];  // 当前弧指针
  int p[NN];    // 可增广路上的上一条弧
  int num[NN];  // 距离标号计数

  void AddEdge(int from, int to, int cap) {
    edges.push_back((Edge){from, to, cap, 0});
    edges.push_back((Edge){to, from, 0, 0});
    m = edges.size();
    G[from].push_back(m - 2), G[to].push_back(m - 1);
  }

  bool BFS() {
    fill_n(vis, n + 1, false);
    queue<int> Q;
    Q.push(t), vis[t] = 1, d[t] = 0;
    while (!Q.empty()) {
      int x = Q.front();
      Q.pop();
      for (size_t i = 0; i < G[x].size(); i++) {
        Edge &e = edges[G[x][i] ^ 1];
        if (!vis[e.from] && e.cap > e.flow)
          vis[e.from] = 1, d[e.from] = d[x] + 1, Q.push(e.from);
      }
    }
    return vis[s];
  }

  void ClearAll(int n) {
    this->n = n;
    for (int i = 0; i < n; i++)
      G[i].clear();
    edges.clear();
  }

  void ClearFlow() {
    for (size_t i = 0; i < edges.size(); i++)
      edges[i].flow = 0;
  }

  int Augment() {
    int x = t, a = INF;
    while (x != s) {
      Edge &e = edges[p[x]];
      a = min(a, e.cap - e.flow), x = edges[p[x]].from;
    }
    x = t;
    while (x != s)
      edges[p[x]].flow += a, edges[p[x] ^ 1].flow -= a, x = edges[p[x]].from;
    return a;
  }

  int Maxflow(int s, int t, int need) {
    this->s = s, this->t = t;
    int flow = 0;
    BFS();
    fill_n(num, n + 1, 0);
    for (int i = 0; i < n; i++)
      num[d[i]]++;
    int x = s;
    fill_n(cur, n + 1, 0);
    while (d[s] < n) {
      if (x == t) {
        flow += Augment();
        if (flow >= need)
          return flow;
        x = s;
      }
      int ok = 0;
      for (size_t i = cur[x]; i < G[x].size(); i++) {
        Edge &e = edges[G[x][i]];
        if (e.cap > e.flow && d[x] == d[e.to] + 1) { // Advance
          ok = 1, p[e.to] = G[x][i], cur[x] = i;     // 注意
          x = e.to;
          break;
        }
      }
      if (!ok) {       // Retreat
        int m = n - 1; // 初值注意
        for (size_t i = 0; i < G[x].size(); i++) {
          Edge &e = edges[G[x][i]];
          if (e.cap > e.flow)
            m = min(m, d[e.to]);
        }
        if (--num[d[x]] == 0)
          break;
        num[d[x] = m + 1]++, cur[x] = 0; // 注意
        if (x != s)
          x = edges[p[x]].from;
      }
    }
    return flow;
  }

  vector<int> Mincut() { // call this after maxflow
    BFS();
    vector<int> ans;
    for (size_t i = 0; i < edges.size(); i++) {
      Edge &e = edges[i];
      if (!vis[e.from] && vis[e.to] && e.cap > 0)
        ans.push_back(i);
    }
    return ans;
  }

  void Reduce() {
    for (size_t i = 0; i < edges.size(); i++)
      edges[i].cap -= edges[i].flow;
  }

  void print() {
    printf("Graph:\n");
    for (size_t i = 0; i < edges.size(); i++) {
      const Edge &e = edges[i];
      printf("%d->%d, %d, %d\n", e.from, e.to, e.cap, e.flow);
    }
  }
};

ISAP g;
void solve(int n, int c) {
  int flow = g.Maxflow(0, n - 1, INF);
  if (flow >= c) {
    puts("possible");
    return;
  }
  vector<int> cut = g.Mincut();
  g.Reduce(); // 保留以前的流量
  vector<Edge> ans;
  for (size_t i = 0; i < cut.size(); i++) {
    Edge &e = g.edges[cut[i]];
    e.cap = c, g.ClearFlow();
    if (flow + g.Maxflow(0, n - 1, c) >= c) ans.push_back(e);
    e.cap = 0;
  }
  if (ans.empty()) {
    puts("not possible");
    return;
  }
  sort(ans.begin(), ans.end());
  printf("possible option:(%d,%d)", ans[0].from + 1, ans[0].to + 1);
  for (size_t i = 1; i < ans.size(); i++)
    printf(",(%d,%d)", ans[i].from + 1, ans[i].to + 1);
  puts("");
}

int main() {
  for (int n, e, c, kase = 1; scanf("%d%d%d", &n, &e, &c) == 3 && n; kase++) {
    g.ClearAll(n);
    for (int i = 0, b1, b2, fp; i < e; i++)
      scanf("%d%d%d", &b1, &b2, &fp), g.AddEdge(b1 - 1, b2 - 1, fp);
    printf("Case %d: ", kase);
    solve(n, c);
  }
  return 0;
}
// Accepted 360ms 4250 C++ 5.3.0 2020-12-1418:43:39 25846863