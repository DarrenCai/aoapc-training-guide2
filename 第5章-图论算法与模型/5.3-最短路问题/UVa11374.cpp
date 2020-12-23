// 例题11  机场快线（Airport Express, UVa 11374）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
typedef long long LL;
struct Edge {
  int u, v, d;
  bool operator<(const Edge& e) const { return d < e.d; }
};

struct HeapNode {
  int u, d;
  bool operator<(const HeapNode& rhs) const { return d > rhs.d; }
};

template <int SZV, int INF>  // |V|
struct Dijkstra {
  int n;
  vector<Edge> edges;
  vector<int> G[SZV];
  bool done[SZV];
  int d[SZV], p[SZV];

  void init(int n) {
    assert(n < SZV);
    this->n = n;
    edges.clear();
    _for(i, 0, n) G[i].clear();
  }

  void addEdge(int u, int v, int d) {  // u-v,d
    G[u].push_back(edges.size()), edges.push_back({u, v, d});
  }

  void dijkstra(int s) {
    priority_queue<HeapNode> Q;
    fill_n(done, n, false), fill_n(d, n, INF);
    d[s] = 0, Q.push({s, 0});
    while (!Q.empty()) {
      HeapNode x = Q.top();
      Q.pop();
      int u = x.u;  // select a node nearest to the current node set
      if (done[u]) continue;
      done[u] = true;

      for (size_t ei = 0; ei < G[u].size(); ei++) {
        const auto& e = edges[G[u][ei]];
        int v = e.v;
        if (d[v] > d[u] + e.d)
          d[v] = d[u] + e.d, p[v] = G[u][ei], Q.push({v, d[v]});
      }
    }
  }

  // path of s->e
  void getPath(int s, int e, deque<int>& path, bool rev = false) {
    assert(d[s] == 0), assert(d[e] != INF);
    int x = e;
    if (rev) path.push_back(x);
    else path.push_front(x);
    while (x != s) {
      x = edges[p[x]].u;
      if (rev) path.push_back(x);
      else path.push_front(x);
    }
  }
};

const int MAXN = 500 + 4, INF = 1e9;
int main() {
  Dijkstra<MAXN, INF> SD, ED;  // S -> * , E -> *
  for (int t = 0, N, S, E, M, K, u, v, d; scanf("%d%d%d", &N, &S, &E) == 3; t++) {
    if (t) puts("");
    SD.init(N + 1), ED.init(N + 1);
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {  // Economy-Xpress
      scanf("%d%d%d", &u, &v, &d);
      SD.addEdge(u, v, d), SD.addEdge(v, u, d);
      ED.addEdge(u, v, d), ED.addEdge(v, u, d);
    }
    SD.dijkstra(S), ED.dijkstra(E);
    int cu = -1, ans = INF;
    deque<int> path;
    if (SD.d[E] < ans) ans = SD.d[E], SD.getPath(S, E, path);

    auto update = [&](int u, int v, int d) {  // S -> u -> v -> E;
      if (SD.d[u] < ans && ED.d[v] < ans && SD.d[u] + d + ED.d[v] < ans) {
        ans = SD.d[u] + d + ED.d[v], cu = u, path.clear();
        SD.getPath(S, u, path), ED.getPath(E, v, path, true);
      }
    };

    scanf("%d", &K);
    _for(i, 0, K)
      scanf("%d%d%d", &u, &v, &d), update(u, v, d), update(v, u, d);
    _for(i, 0, path.size()) {
      if (i) printf(" ");
      printf("%d", path[i]);
    }
    puts("");
    if (cu == -1) puts("Ticket Not Used");
    else printf("%d\n", cu);
    printf("%d\n", ans);
  }
  return 0;
}
// 18869546 11374 Airport Express Accepted C++11 0.000 2017-03-01 03:10:33