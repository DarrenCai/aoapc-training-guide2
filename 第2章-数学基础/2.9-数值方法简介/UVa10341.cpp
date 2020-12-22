// 例题36  解方程（Solve It!, UVa 10341）
// 刘汝佳
#include<cstdio>
#include<cmath>
#include <iostream>
#define F(x) (p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*(x)*(x)+u)
using namespace std;
const double eps = 1e-14;
int main() {
  for(int p, r, q, s, t, u; cin>>p>>q>>r>>s>>t>>u; ) {
    double f0 = F(0), f1 = F(1);
    if(f1 > eps || f0 < -eps) {
      puts("No solution");
      continue;
    }
    double x = 0, y = 1, m;
    for(int i = 0; i < 100; i++) {
      m = x + (y-x)/2;
      if(F(m) < 0) y = m; else x = m;
    }
    printf("%.4lf\n", m);
  }
  return 0;
}
// Accepted 10ms 548 C++5.3.0 2020-12-12 22:18:30 25840322