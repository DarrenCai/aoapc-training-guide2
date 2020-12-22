// 例题18  开放式学分制（Open Credit System, UVa 11078）
// 陈锋
#include <cassert>
#include <cstdio>
#include <algorithm>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
typedef long long LL;
const int MAXN = 1e5 + 4;
int A[MAXN];
int main() {
  int n, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    _for(i, 0, n) scanf("%d", &(A[i]));
    int m = A[0], ans = A[0] - A[1];  // maxA[i]
    _for(i, 1, n) // m is max{A0, A1, A_{i-1}}      
      ans = max(m - A[i], ans), m = max(A[i], m);
    printf("%d\n", ans);
  }
  return 0;
}
// 18756057	11078	Open Credit System	Accepted	C++11	0.060	2017-02-10 14:12:42
