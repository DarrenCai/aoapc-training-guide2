// 例题9  最大公约数之和——极限版II（GCD Extreme(II), UVa 11426）
// 刘汝佳
#include <cstdio>
#include <cstring>
const int NN = 4000000;
typedef long long LL;

int phi[NN + 1];
void phi_table(int n) {
  for (int i = 2; i <= n; i++) phi[i] = 0;
  phi[1] = 1;
  for (int i = 2; i <= n; i++)
    if (!phi[i])
      for (int j = i; j <= n; j += i) {
        if (!phi[j]) phi[j] = j;
        phi[j] = phi[j] / i * (i - 1);
      }
}
LL S[NN + 1], f[NN + 1];
int main() {
  phi_table(NN);

  // 预处理f
  memset(f, 0, sizeof(f));
  for (int i = 1; i <= NN; i++)
    for (int n = i * 2; n <= NN; n += i) f[n] += i * phi[n / i];

  // 预处理S
  S[2] = f[2];
  for (int n = 3; n <= NN; n++) S[n] = S[n - 1] + f[n];
  for (int n; scanf("%d", &n) == 1 && n;) printf("%lld\n", S[n]);
  return 0;
}
// Accepted 760ms 727 C++ 5.3.0 2020-12-09 17:21:08 25828691