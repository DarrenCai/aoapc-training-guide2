// 例题15  数一数a x b（Count a x b, ACM/ICPC Changchun 2015, LA7184/HDU5528）
// 陈锋
#include <bits/stdc++.h>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
const int MAXN = (int)(1e9) + 4, MAXP = 31622 + 4;
typedef unsigned long long ULL;

// lp:i的最小素因子, primes: 记录所有素数
int lp[MAXP], primes[MAXP], pcnt;
void sieve(int N) {
  pcnt = 0;
  fill_n(lp, N, 0);
  for (int i = 2; i < N; ++i) {
    int& l = lp[i]; // i的最小素因子l
    if (l == 0) l = i, primes[pcnt++] = i; // i是素数
    for (int j = 0; j < pcnt && primes[j] <= l; ++j) {
      int p = primes[j]; // p <= l
      if (i * p >= N) break;
      lp[i * p] = p; // i * p的最小素因子是p
    }
  }
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T, N;
  cin >> T;
  sieve(MAXP);
  while (T--) {
    cin >> N;
    ULL g = 1, h = N, x = N;
    _for(i, 0, pcnt) {
      ULL p = primes[i];
      if (p > x) break;
      if (x % p != 0) continue;
      int k = 0;
      ULL sp = 1, pp = p * p;  // Σp^(2i), p^2i
      for (k = 0; x % p == 0; k++) {
        x /= p;
        sp += pp, pp *= p * p;
      }
      g *= sp, h *= k + 1;
    }
    if (x > 1) g *= (1 + x * x), h *= 2;
    cout << g - h << endl;
  }
  return 0;
}
// 2620236  7184  Count a × b   Accepted  C++11   0.436   2019-12-10 06:01:35