// 例题24  排列统计（Find the Permutations, UVa 11077）
// 刘汝佳
#include <cstdio>
#include <cstring>
const int maxn = 30;
unsigned long long f[maxn][maxn];
int main() {
  memset(f, 0, sizeof(f));
  f[1][0] = 1;
  for (int i = 2; i <= 21; i++)
    for (int j = 0; j < i; j++) {
      f[i][j] = f[i - 1][j];
      if (j > 0) f[i][j] += f[i - 1][j - 1] * (i - 1);
    }
  int n, k;
  while (scanf("%d%d", &n, &k) == 2 && n) printf("%llu\n", f[n][k]);
  return 0;
}
// Accepted 435 C++5.3.0 2020-12-12 20:34:55 25839718