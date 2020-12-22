// 例题13  派（Pie, NWERC 2006, Codeforces Gym100722C）
// 陈锋
#include <bits/stdc++.h>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
typedef long long LL;
const int NN = 10000 + 4;
double S[NN];
const double PI = acos(-1), EPS = 1e-6;

int main() {
  int T; scanf("%d", &T);
  for (int t = 0, N, F; t < T; t++) {
    scanf("%d%d", &N, &F), ++F;
    double L = 0, R = 0, r;
    _for(i, 0, N) scanf("%lf", &r), R = max(R, S[i] = r * r * PI);
    while (L + EPS < R) { // L is always an min answer
      double M = (L + R) / 2; int f = 0;
      _for(i, 0, N) {
        f += (int)floor(S[i] / M);
        if (f >= F) break;
      }
      if (f >= F) L = M; else R = M;
    }
    printf("%.4lf\n", L);
  }
}
// 102050321	Dec/22/2020 22:37UTC+8	chenwz	C - Pie	GNU C++11	Accepted	62 ms	100 KB
