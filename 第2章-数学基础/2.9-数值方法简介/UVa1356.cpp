// 例题38  桥上的绳索（Bridge, Hangzhou 2005, UVa1356）
// 刘汝佳
#include <cmath>
#include <cstdio>

// sqrt(a^2+x^2)的原函数
double F(double a, double x) {
  double a2 = a * a, x2 = x * x;
  return (x * sqrt(a2 + x2) + a2 * log(fabs(x + sqrt(a2 + x2)))) / 2;
}

// 宽度为w，高度为h的抛物线长度，也就是前文中的p(w,h)
double parabola_arc_length(double w, double h) {
  double a = 4.0 * h / (w * w), b = 1.0 / (2 * a);
  // 如果不用对称性，就是(F(b,w/2)-F(b,-w/2))*2*a
  return (F(b, w / 2) - F(b, 0)) * 4 * a;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int kase = 1, D, H, B, L; kase <= T; kase++) {
    scanf("%d%d%d%d", &D, &H, &B, &L);
    int n = (B + D - 1) / D;  // 间隔数
    double D1 = (double)B / n, L1 = (double)L / n, x = 0, y = H;
    while (y - x > 1e-5) {  // 二分法求解高度
      double m = x + (y - x) / 2;
      if (parabola_arc_length(D1, m) < L1) x = m;
      else y = m;
    }
    if (kase > 1) puts("");
    printf("Case %d:\n%.2lf\n", kase, H - x);
  }
  return 0;
}
// 25877139 	1356 	Bridge 	Accepted 	C++ 	0.000 	2020-12-23 03:17:10