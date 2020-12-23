// 例题15  周期（Period, SEERC 2004, Codeforces Gym101461A）
// 陈锋
#include <cstdio>
const int NN = 1e6 + 4;
char P[NN];
int F[NN];

int main() {
  freopen("period.in", "r", stdin);
  freopen("period.out", "w", stdout);

  for (int n, kase = 1; scanf("%d", &n) == 1 && n; kase++) {
    scanf("%s", P);
    F[0] = 0, F[1] = 0;  // 递推边界初值
    for (int i = 1; i < n; i++) {
      int j = F[i];
      while (j && P[i] != P[j]) j = F[j];
      F[i + 1] = (P[i] == P[j] ? j + 1 : 0);
    }

    printf("Test case #%d\n", kase);
    for (int i = 2; i <= n; i++)
      if (F[i] > 0 && i % (i - F[i]) == 0) printf("%d %d\n", i, i / (i - F[i]));
    printf("\n");
  }
  return 0;
}
// 102087071  Dec/23/2020 12:10UTC+8  chenwz  A - Period  GNU C++11  Accepted  46 ms  4800 KB