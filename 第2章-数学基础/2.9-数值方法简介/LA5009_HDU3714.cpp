// 例题37  误差曲线（Error Curves, Chengdu 2010, LA5009）
// 刘汝佳
#include <algorithm>
#include <cstdio>
using namespace std;
const int NN = 10000 + 10;
int T, n, a[NN], b[NN], c[NN];
double F(double x) {
  double ans = a[0] * x * x + b[0] * x + c[0];
  for (int i = 1; i < n; i++) ans = max(ans, a[i] * x * x + b[i] * x + c[i]);
  return ans;
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d%d", &a[i], &b[i], &c[i]);
    double L = 0.0, R = 1000.0;
    for (int i = 0; i < 100; i++) {
      double m1 = L + (R - L) / 3, m2 = R - (R - L) / 3;
      if (F(m1) < F(m2)) R = m2;
      else L = m1;
    }
    printf("%.4lf\n", F(L));
  }
  return 0;
}
// 34852546 2020-12-12 22:21:37 Accepted 3714 280MS 1344K 686 B G++