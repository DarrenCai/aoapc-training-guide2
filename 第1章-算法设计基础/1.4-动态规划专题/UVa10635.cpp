// 例题27  王子和公主（Prince and Princess, UVa 10635）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 256, MAXP = MAXN * MAXN;
using namespace std;
typedef long long LL;
int B[MAXP], IDX[MAXP], D[MAXP];

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T, n, a, p, q;
  cin >> T;
  for (int t = 1; cin >> n >> p >> q && n; t++) {
    ++p, ++q;
    fill_n(IDX, n * n + 2, 0);
    for (int i = 1; i <= p; i++) cin >> a, IDX[a] = i;
    int bi = 0, b;
    for (int i = 0; i < q; i++) {
      cin >> b, b = IDX[b];
      if (b) B[bi++] = b;
    }
    fill_n(D, bi + 1, 1); // 计算B的LIS
    int ans = -1;
    for (int i = 0; i < bi; i++) {
      for (int j = i + 1; j < bi; j++)
        if (B[j] > B[i]) D[j] = max(D[j], 1 + D[i]);
      ans = max(ans, D[i]);
    }
    printf("Case %d: %d\n", t, ans);
  }
  return 0;
}
// Accepted 2250ms 826 C++5.3.0 2020-12-08 20:27:25 25825777