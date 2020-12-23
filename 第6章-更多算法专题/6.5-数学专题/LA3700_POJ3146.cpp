// LA3700/POJ3146 Interesting Yang Hui Triangle, Asia上海 2016
// 刘汝佳
#include <cstdio>
int main() {
  for (int kase = 0, n, p; scanf("%d%d", &p, &n) == 2 && p;) {
    int ans = 1;
    while (n > 0) ans = ans * (n % p + 1) % 10000, n /= p;
    printf("Case %d: %04d\n", ++kase, ans);
  }
  return 0;
}
// Accepted 328kB 298 G++ 2020-12-12 22:41:35 22206289