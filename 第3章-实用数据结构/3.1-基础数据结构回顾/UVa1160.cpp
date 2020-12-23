// 例题5  易爆物（X-Plosives, UVa1160）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
typedef long long LL;
const int MAXN = 100000 + 4;
int Pa[MAXN];

int findPa(int u) {
  return Pa[u] == u ? u : (Pa[u] = findPa(Pa[u]));
}

int main() {
  int u, v;
  while (true) {
    _rep(i, 0, MAXN) Pa[i] = i;
    int ans = 0;
    while (true) {
      if (scanf("%d", &u) != 1) return 0;
      if (u == -1) break;
      scanf("%d", &v);
      int pu = findPa(u), pv = findPa(v);
      if (pu == pv)
        ans++;
      else
        Pa[pu] = v;
    }
    printf("%d\n", ans);
  }
  return 0;
}
// Accepted 751 C++5.3.0 2020-12-1319:42:07 25843348