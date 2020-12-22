// 例题26  约瑟夫问题的变形（And Then There Was One, Japan 2007, Codeforces Gym101415A
// Rujia Liu
#include<cstdio>
const int maxn = 10000 + 2;
int f[maxn];

int main() {
  freopen("A.in", "r", stdin);
  for( int n, k, m; scanf("%d%d%d", &n, &k, &m) == 3 && n;) {
    f[1] = 0;
    for(int i = 2; i <= n; i++) f[i] = (f[i-1] + k) % i;
    int ans = (m - k + 1 + f[n]) % n;
    if (ans <= 0) ans += n;
    printf("%d\n", ans);
  }
  return 0;
}
// 102052339 Dec/22/2020 23:00UTC+8 chenwz A - And Then There Was One GNU C++11 Accepted 15 ms 0 KB