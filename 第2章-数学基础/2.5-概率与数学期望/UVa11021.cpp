// UVa11021 Tribles
// 陈锋
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long LL;
const int MAXN = 1000 + 4;
double P[MAXN], F[MAXN];
int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1, n, k, m; t <= T; t++) {
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 0; i < n; i++) scanf("%lf", &(P[i]));
    F[0] = 0, F[1] = P[0];
    for (int x = 2; x <= m; x++) {
      F[x] = 0;
      for (int i = 0; i < n; i++) F[x] += P[i] * pow(F[x - 1], i);
    }
    printf("Case #%d: %.7lf\n", t, pow(F[m], k));
  }
  return 0;
}
// 25838816 11021 Tribles Accepted C++ 0.050 2020-12-12 08:28:17