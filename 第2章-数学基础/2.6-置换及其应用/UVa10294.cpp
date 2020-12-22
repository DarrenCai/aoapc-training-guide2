// 例题22  项链和手镯（Arif in Dhaka(First Love Part 2), UVa 10294）
// 陈锋
#include <cstdio>
typedef long long LL;
const int NN = 100;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
  for (int n, t; scanf("%d%d", &n, &t) == 2 && n;) {
    LL pow[NN], a = 0, b = 0;
    pow[0] = 1;
    for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * t;
    for (int i = 0; i < n; i++) a += pow[gcd(i, n)];
    if (n % 2 == 1)
      b = n * pow[(n + 1) / 2];
    else
      b = n / 2 * (pow[n / 2 + 1] + pow[n / 2]);
    printf("%lld %lld\n", a / n, (a + b) / 2 / n);
  }
  return 0;
}
// Accepted 583 C++5.3.0 2020-12-12 17:34:43 25839147