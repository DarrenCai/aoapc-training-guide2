// 例题23  蚂蚁（Ants, NEERC 2008, LA 4043/POJ3565
// 陈锋
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cassert>
using namespace std;

const double INF = 1e30;
template<size_t SZ>
struct KM {
  double W[SZ][SZ]; // 权值
  double Lx[SZ], Ly[SZ];   // 顶标
  int n, left[SZ];          // left[i]为右边第i个点的匹配点编号
  bool S[SZ], T[SZ];   // S[i]和T[i]为左/右第i个点是否已标记

  bool eq(double a, double b) { return fabs(a - b) < 1e-9; }

  void init(size_t _n) {
    assert(_n < SZ);
    this->n = _n;
  }

  bool match(int i) {
    S[i] = true;
    for (int j = 1; j <= n; j++) if (eq(Lx[i] + Ly[j], W[i][j]) && !T[j]) {
        T[j] = true;
        if (!left[j] || match(left[j])) {
          left[j] = i;
          return true;
        }
      }
    return false;
  }

  void update() {
    double a = INF;
    for (int i = 1; i <= n; i++) if (S[i])
        for (int j = 1; j <= n; j++) if (!T[j])
            a = min(a, Lx[i] + Ly[j] - W[i][j]);
    for (int i = 1; i <= n; i++) {
      if (S[i]) Lx[i] -= a;
      if (T[i]) Ly[i] += a;
    }
  }

  void solve() {
    for (int i = 1; i <= n; i++) {
      left[i] = Lx[i] = Ly[i] = 0;
      for (int j = 1; j <= n; j++)
        Lx[i] = max(Lx[i], W[i][j]);
    }
    for (int i = 1; i <= n; i++) {
      for (;;) {
        for (int j = 1; j <= n; j++) S[j] = T[j] = 0;
        if (match(i)) break; else update();
      }
    }
  }
};

const int NN = 100 + 10;
KM<NN> solver;
int main() {
  for (int kase = 1, n; scanf("%d", &n) == 1; kase++) {
    if (kase > 1) printf("\n");
    solver.init(n);
    int x1[NN], y1[NN], x2[NN], y2[NN];
    for (int i = 1; i <= n; i++)
      scanf("%d%d", &x1[i], &y1[i]);
    for (int i = 1; i <= n; i++)
      scanf("%d%d", &x2[i], &y2[i]);
    for (int i = 1; i <= n; i++) // ant colony
      for (int j = 1; j <= n; j++) // apple tree
        solver.W[j][i] = -sqrt((double)(x1[i] - x2[j]) * (x1[i] - x2[j]) + (double)(y1[i] - y2[j]) * (y1[i] - y2[j]));
    solver.solve(); // 最大权匹配
    for (int i = 1; i <= n; i++) printf("%d\n", solver.left[i]);
  }
  return 0;
}
// Accepted 113ms 2066 C++11 5.3.02020-02-0212:09:15