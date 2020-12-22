// 例题35  异或路径(XOR Path, ACM/ICPC, Asia-Dhaka 2017, UVa13277)
// 陈锋
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
static const int maxn = 1e5 + 5, N = 1 << 16;
template <typename T = int>
struct FWT {
  void fwt(T A[], int n) {
    for (int d = 1; d < n; d <<= 1) {
      for (int i = 0, m = d << 1; i < n; i += m) {
        for (int j = 0; j < d; j++) {
          T x = A[i + j], y = A[i + j + d];
          A[i + j] = (x + y), A[i + j + d] = (x - y); // xor
          //A[i+j] = x+y;                     // and
          //A[i+j+d] = x+y;                   // or
        }
      }
    }
  }
  void ufwt(T A[], int n)  {
    for (int d = 1; d < n; d <<= 1)    {
      for (int i = 0, m = d << 1; i < n; i += m) {
        for (int j = 0; j < d; j++) {
          T x = A[i + j], y = A[i + j + d];
          A[i + j] = (x + y) >> 1, A[i + j + d] = (x - y) >> 1; // xor
          //A[i+j] = x-y;                          // and
          //A[i+j+d] = y-x;                        // or
        }
      }
    }
  }

  void conv(T a[], T b[], int n)  {
    fwt(a, n), fwt(b, n);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i];
    ufwt(a, n);
  }

  void self_conv(T a[], int n) {
    fwt(a, n);
    for (int i = 0; i < n; i++) a[i] = a[i] * a[i];
    ufwt(a, n);
  }
};

struct Edge {
  int v, w;
  Edge(int _v = 0, int _w = 0) : v(_v), w(_w) {}
};

vector<Edge> G[maxn];
FWT<LL> fwt;
LL A[N + 5];
void dfs(int u, int p = -1, int x = 0) {
  A[x]++;
  for (auto &e : G[u]) if (e.v != p) dfs(e.v, u, x ^ e.w);
}

int main() {
  int T; scanf("%d", &T);
  for (int t = 1, n; t <= T; t++) {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) G[i].clear();
    fill(begin(A), end(A), 0);
    for (int e = 1, u, v, w; e < n; e++) {
      scanf("%d %d %d", &u, &v, &w);
      G[u].push_back(Edge(v, w)), G[v].push_back(Edge(u, w));
    }
    dfs(1);
    fwt.self_conv(A, N);
    printf("Case %d:\n", t);
    printf("%lld\n", (A[0] - n) / 2);
    for (int i = 1; i < (1 << 16); i++) printf("%lld\n", A[i] / 2);
  }
}
// 24926296 13277 XOR Path  Accepted  C++11 0.350 2020-04-24 15:32:51