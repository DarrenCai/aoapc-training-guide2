// 例题17  年龄排序（Age Sort, UVa 11462）
// 陈锋
#include <bits/stdc++.h>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
typedef long long LL;
const int MAXN = 100;
int main() {
  int n, a, cnt[MAXN + 4];
  while (scanf("%d", &n) == 1 && n) {
    fill_n(cnt, MAXN + 4, 0);
    _for(i, 0, n) scanf("%d", &a), ++cnt[a];
    _for(i, 0, MAXN) _for(j, 0, cnt[i])
      printf("%d%s", i, (i == MAXN - 1 && j == cnt[i] - 1) ? "" : " ");
    puts("");
  }
}
// 25875806	11462	Age Sort	Accepted	C++	0.250	2020-12-22 14:38:05