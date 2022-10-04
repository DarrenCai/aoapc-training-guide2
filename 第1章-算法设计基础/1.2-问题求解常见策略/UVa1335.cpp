// 例题16  长城守卫（Beijing Guards, CERC 2004, UVa1335）
// Rujia Liu
#include <bits/stdc++.h>
#define _all(i, a, b) for (int i = (a); i <= (int)(b); ++i)
using namespace std;
const int NN = 1e5 + 4;
// 测试p个礼物是否足够, Lᵢ,Rᵢ是第i个人拿到的“左≤(r₁)/右(>r₁)的礼物”总数
int N, A[NN], L[NN], R[NN];
bool test(int p) {
  int lc = A[1], rc = p - A[1];
  L[1] = lc, R[1] = 0;
  _all(i, 2, N) {
    if (i % 2)
      R[i] = min(rc - R[i - 1], A[i]), L[i] = A[i] - R[i]; // 尽量拿右边的礼物
    else
      L[i] = min(lc - L[i - 1], A[i]), R[i] = A[i] - L[i]; // 尽量拿左边的礼物
  }
  return L[N] == 0; // 跟1都不冲突
}
int solve() {
  if (N == 1) return A[1]; // 特判n=1
  A[N + 1] = A[1];
  int l = 0, r = 0;
  _all(i, 1, N) l = max(l, A[i] + A[i + 1]), r = max(r, A[i] * 3);
  while (N % 2 && l < r) {
    int m = l + (r - l) / 2;
    if (test(m)) r = m;
    else l = m + 1;
  }
  return l;
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  while (cin >> N && N) {
    _all(i, 1, N) cin >> A[i];
    cout << solve() << endl;
  }
  return 0;
}
// 25875801	1335	Beijing Guards	Accepted	C++	0.010	2020-12-22 14:37:13