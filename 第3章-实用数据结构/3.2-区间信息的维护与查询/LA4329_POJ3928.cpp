// 例题7  乒乓比赛（Ping pong, Beijing 2008, LA4329）
// 陈锋
#include <cassert>
#include <iostream>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
typedef long long LL;

template <typename T, size_t SZ>
struct BIT {  // Binary Indexed Tree
  T C[SZ];
  size_t N;
  inline void init(size_t sz) {
    N = sz;
    assert(N + 1 < SZ);
    fill_n(C, N + 1, 0);
  }
  inline int lowbit(int x) { return x & -x; }
  inline T sum(size_t i) {  // Σ(k = 1→i)
    T ans = 0;
    while (i > 0) ans += C[i], i -= lowbit(i);
    return ans;
  }

  inline void add(size_t i, const T& v) {
    while (i <= N) C[i] += v, i += lowbit(i);
  }
};

const int MAXN = 20000 + 4, MAXA = 1e5;
int A[MAXN], C[MAXN], D[MAXN];
/*
  i当裁判，考虑a[1~i-1]中有ci个比ai小，(i-1)-ci个比ai大,
  a[i+1~n]有di个比ai小，(n-i-di)个比ai大
  则i当裁判就有ci(n-i-di)+(i-1-ci)di种比赛，求Σ即可
  ci, di扫描求得，X[a] = 1 -> exist Ai = a before
*/
int main() {
  int T, N;
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> T;
  BIT<int, MAXA + 4> X;
  while (T--) {
    cin >> N, fill_n(C, N + 1, 0);
    X.init(MAXA);
    _rep(i, 1, N) cin >> A[i], C[i] = X.sum(A[i] - 1), X.add(A[i], 1);
    X.init(MAXA);
    LL ans = 0;
    for (int i = N; i >= 1; i--) {
      int d = X.sum(A[i] - 1);
      X.add(A[i], 1);
      if (i < N && i > 1) ans += C[i] * (N - i - d) + (i - 1 - C[i]) * d;
    }
    cout << ans << endl;
  }
  return 0;
}
// Accepted 719ms 1184kB 1504 G++2020-12-13 20:47:28 22208011
