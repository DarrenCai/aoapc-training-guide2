// 例题13  战争和物流（Warfare and Logistics, LA4080/UVa1416）
// 陈锋
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int INF = 1e9, NN = 100 + 8;
struct Edge { int from, to, dist; };
struct HeapNode {
  int d, u;
  bool operator < (const HeapNode& rhs) const {
    return d > rhs.d;
  }
};

template<size_t SZ>
struct Dijkstra {
  int n, m;
  vector<Edge> edges;
  vector<int> G[SZ];
  bool done[SZ];		//是否已永久标号
  int d[SZ];			//s到各个点的距离
  int p[SZ];			//最短路中的上一条弧

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int dist) {
    edges.push_back((Edge) {from, to, dist});
    m = edges.size();
    G[from].push_back(m - 1);
  }

  void dijkstra(int s) {
    priority_queue<HeapNode> Q;
    for (int i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    Q.push((HeapNode) {0, s});
    while (!Q.empty()) {
      HeapNode x = Q.top(); Q.pop();
      int u = x.u;
      if (done[u]) continue;
      done[u] = true;
      for (size_t i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if (e.dist > 0 && d[e.to] > d[u] + e.dist) {
          //此处和模板不同，忽略了dist = -1的边。
          // 此为删除标记。
          // 根据题意和dijkstra算法的前提，正常的边dist > 0
          d[e.to] = d[u] + e.dist;
          p[e.to] = G[u][i];
          Q.push((HeapNode) {d[e.to], e.to});
        }
      }
    }
  }
};

//题目相关
Dijkstra<NN> solver;
int N, M, L;
vector<int> gr[NN][NN];	//两点之间的原始边权
int used[NN][NN][NN]; //used[src][a][b]表示源点为src的最短路树是否包含边a->b
int idx[NN][NN];      //idx[u][v]为边u->v在Dijkstra求解器中的编号
int sum_single[NN]; //sum_single[src]表示源点为src的最短路树的所有d之和

int compute_c() {
  int ans = 0;
  memset(used, 0, sizeof(used));
  for (int src = 0; src < N; src++) {
    solver.dijkstra(src);
    sum_single[src] = 0;
    for (int i = 0; i < N; i++) {
      if (i != src) {
        int fa = solver.edges[solver.p[i]].from;
        used[src][fa][i] = used[src][i][fa] = 1;
      }
      sum_single[src] += (solver.d[i] == INF ? L : solver.d[i]);
    }
    ans += sum_single[src];
  }
  return ans;
}

int compute_newc(int a, int b) {
  int ans = 0;
  for (int src = 0; src < N; src++)
    if (!used[src][a][b]) ans += sum_single[src];
    else {
      solver.dijkstra(src);
      for (int i = 0; i < N; i++)
        ans += (solver.d[i] == INF ? L : solver.d[i]);
    }
  return ans;
}

int main() {
  while (scanf("%d%d%d", &N, &M, &L) == 3) {
    solver.init(N);
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) gr[i][j].clear();

    for (int i = 0, a, b, s; i < M; i++) {
      scanf("%d%d%d", &a, &b, &s), a--, b--;
      gr[a][b].push_back(s), gr[b][a].push_back(s);
    }

    //构造网络
    for (int i = 0; i < N; i++)
      for (int j = i + 1; j < N; j++) if (!gr[i][j].empty()) {
          sort(gr[i][j].begin(), gr[i][j].end());
          solver.AddEdge(i, j, gr[i][j][0]);
          idx[i][j] = solver.m - 1;
          solver.AddEdge(j, i, gr[i][j][0]);
          idx[j][i] = solver.m - 1;
        }

    int c = compute_c(), c2 = -1;
    for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++)
        if (!gr[i][j].empty()) {
          int& e1 = solver.edges[idx[i][j]].dist;
          int& e2 = solver.edges[idx[j][i]].dist;
          if (gr[i][j].size() == 1) e1 = e2 = -1;
          else e1 = e2 = gr[i][j][1]; //第一、第二短的边
          c2 = max(c2, compute_newc(i, j));
          e1 = e2 = gr[i][j][0]; //恢复
        }

    printf("%d %d\n", c, c2);
  }
  return 0;
}
// Accepted 230ms 3538 C++ 5.3.0 2020-12-14 17:00:37 25846446