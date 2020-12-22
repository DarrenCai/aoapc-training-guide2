// 例题10  正整数序列（Help is needed for Dexter, UVa 11384）
// Rujia Liu
#include<cstdio>
int f(int n) {
  return n == 1 ? 1 : f(n/2) + 1;
}

int main() {
  int n;
  while(scanf("%d", &n) == 1)
    printf("%d\n", f(n));
  return 0;
}
// 25875779	11384	Help is needed for Dexter	Accepted	C++	0.020	2020-12-22 14:31:10