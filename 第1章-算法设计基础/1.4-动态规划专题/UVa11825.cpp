// 例题29  黑客的攻击（Hacker’s Crackdown, UVa 11825）
// 陈锋
#include <algorithm>
#include <cstdio>
using namespace std;

const int NN = 16;
int P[NN], cover[1 << NN], f[1 << NN];
int main() {
  for (int kase = 1, n; scanf("%d", &n) == 1 && n; kase++) {
    for (int i = 0, m, x; i < n; i++) {
      scanf("%d", &m), P[i] = 1 << i;
      while (m--) scanf("%d", &x), P[i] |= (1 << x);
    }
    for (int S = 0; S < (1 << n); S++) {
      cover[S] = 0;
      for (int i = 0; i < n; i++)
        if (S & (1 << i)) cover[S] |= P[i];
    }
    f[0] = 0;
    int ALL = (1 << n) - 1;
    for (int S = 1; S < (1 << n); S++) {
      f[S] = 0;
      for (int S0 = S; S0; S0 = (S0 - 1) & S)
        if (cover[S0] == ALL) f[S] = max(f[S], f[S ^ S0] + 1);
    }
    printf("Case %d: %d\n", kase, f[ALL]);
  }
  return 0;
}
// Accepted 720ms 795 C++5.3.02020-12-08 21:14:04 25825962