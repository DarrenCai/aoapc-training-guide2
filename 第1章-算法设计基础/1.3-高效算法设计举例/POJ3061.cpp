// 例题21  子序列（Subsequence, SEERC 2006, POJ3061）
// 陈锋
#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 1e5 + 8;
int A[maxn], B[maxn], T;
int main() {
  scanf("%d", &T);
  for (int n, S; scanf("%d%d", &n, &S) == 2 && T--;) {
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    B[0] = 0;
    for (int i = 1; i <= n; i++) B[i] = B[i - 1] + A[i];
    int ans = n + 1, i = 1;
    for (int j = 1; j <= n; j++) {
      if (B[i - 1] > B[j] - S) continue;  // (1)没有满足条件的i，换下一个j
      while (B[i] <= B[j] - S) i++;  // (2)求满足B[i-1]<=B[j]-S的最大i
      ans = min(ans, j - i + 1);
    }
    printf("%d\n", ans == n + 1 ? 0 : ans);
  }
  return 0;
}
// Accepted 79ms 1104kB 731 G++2020-12-24 10:55:33 22229063