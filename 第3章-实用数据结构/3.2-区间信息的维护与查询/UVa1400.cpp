// 例题9  动态最大连续和（Ray, Pass me the Dishes, UVa1400）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int, int> Interval;
const int MAXN = 5e5 + 4;
LL SD[MAXN];
inline LL sum(int L, int R) { // [L,R]
  // assert(L <= R);
  return SD[R] - SD[L - 1];
}
inline LL sum(const Interval& i) { return sum(i.first, i.second); }
inline Interval maxI(const Interval& i1, const Interval& i2) {
  LL s1 = sum(i1), s2 = sum(i2);
  if (s1 != s2) return s1 > s2 ? i1 : i2;
  return min(i1, i2);
}
struct MaxVal {
  int pfx, sfx;
  Interval sub;
};

struct IntervalTree {
  MaxVal Nodes[MAXN * 2];
  int qL, qR, N;
  void build(int N) { // [1, N]
    this->N = N;
    build(1, N, 1);
  }

  void build(int L, int R, int O) {
    assert(L <= R);
    assert(O > 0);
    if (L == R) {
      Nodes[O] = {L, L, make_pair(L, L)};
      return;
    }
    int M = (L + R) / 2, lc = 2 * O, rc = 2 * O + 1;
    build(L, M, lc), build(M + 1, R, rc);
    const MaxVal &nl = Nodes[lc], &nr = Nodes[rc];
    MaxVal &no = Nodes[O];
    no.pfx = sum(L, nl.pfx) >= sum(L, nr.pfx) ? nl.pfx : nr.pfx;
    no.sfx = sum(nl.sfx, R) >= sum(nr.sfx, R) ? nl.sfx : nr.sfx;
    no.sub = maxI(nl.sub, nr.sub);
    no.sub = maxI(no.sub, make_pair(nl.sfx, nr.pfx));
  }

  Interval query(int l, int r) { // max sub [a,b] in [l, r]
    assert(l <= r);
    qL = l, qR = r;
    return _query(1, N, 1);
  }

  Interval _query(const int L, const int R, const int O) {
    if (qL <= L && R <= qR) return Nodes[O].sub;
    int M = (L + R) / 2, lc = O * 2, rc = 2 * O + 1;
    if (qR <= M) return _query(L, M, lc);
    if (qL > M) return _query(M + 1, R, rc);
    Interval ans = make_pair(_querySfx(L, M, lc), _queryPfx(M + 1, R, rc));
    ans = maxI(ans, maxI(_query(L, M, lc), _query(M + 1, R, rc)));
    return ans;
  }

  int _queryPfx(const int L, const int R, const int O) {
    if (qL <= L && R <= qR) return Nodes[O].pfx;
    int M = (L + R) / 2, lc = 2 * O, rc = 2 * O + 1;
    if (qR <= M) return _queryPfx(L, M, lc);
    if (qL > M) return _queryPfx(M + 1, R, rc);
    int m1 = _queryPfx(L, M, lc), m2 = _queryPfx(M + 1, R, rc);
    return sum(L, m1) >= sum(L, m2) ? m1 : m2;
  }

  int _querySfx(const int L, const int R, const int O) {
    if (qL <= L && R <= qR) return Nodes[O].sfx;
    int M = (L + R) / 2, lc = O * 2, rc = 2 * O + 1;
    if (qR <= M) return _querySfx(L, M, lc);
    if (qL > M) return _querySfx(M + 1, R, rc);
    int m1 = _querySfx(L, M, lc), m2 = _querySfx(M + 1, R, rc);
    return sum(m1, R) >= sum(m2, R) ? m1 : m2;
  }
};
IntervalTree tree;

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  SD[0] = 0;
  for (int t = 1, d, a, b, N, M; cin >> N >> M; t++) {
    _rep(i, 1, N) cin >> d, SD[i] = SD[i - 1] + d;
    tree.build(N);
    printf("Case %d:\n", t);
    _rep(i, 1, M) {
      cin >> a >> b;
      Interval ans = tree.query(a, b);
      printf("%d %d\n", ans.first, ans.second);
    }
  }
  return 0;
}
// Accepted 160ms 3130 C++ 5.3.0 2020-12-13 20:58:55 25843597