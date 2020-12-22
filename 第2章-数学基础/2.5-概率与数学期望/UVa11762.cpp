// UVa11762 Race To 1
// 陈锋
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int NN = 1e6 + 10;
double F[NN];
int IsPrime[NN], primes[NN], vis[NN];

void gen_primes(int n) {
  fill_n(IsPrime, n + 1, 1);
  for (int i = 2, p = 0; i <= n; i++) {
    if (!IsPrime[i]) continue;
    primes[p++] = i;
    if (i <= n / i)
      for (int j = i * i; j <= n; j += i) IsPrime[j] = 0;
  }
}

double dp(int x) {
  double& f = F[x];
  if (x == 1) return 0.0;  // 边界
  if (vis[x]) return f;    // 记忆化
  vis[x] = 1;
  int g = 0, p = 0;  // 累加g(x)和p(x)
  f = 0;
  for (int i = 0; primes[i] <= x; i++) {
    p++;
    if (x % primes[i] == 0) g++, f += dp(x / primes[i]);
  }
  return f = (f + p) / g;
}

int main() {
  int T;
  scanf("%d", &T);
  gen_primes(NN - 1), fill_n(vis, NN, 0);
  for (int kase = 1, n; kase <= T; kase++) {
    scanf("%d", &n);
    printf("Case %d: %.10lf\n", kase, dp(n));
  }
  return 0;
}
// Accepted 190ms 964 C++ 5.3.0 2020-12-12 16:51:29 25838925