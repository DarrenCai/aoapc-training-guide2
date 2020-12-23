// 例题47 流星（Meteors，POI2011，SPOJ METEORS）
// 陈锋
#include<bits/stdc++.h>
#define _for(i,a,b) for(int i=(a); i<(int)(b); ++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
typedef long long LL;
template<int SZ>
struct BIT {
  LL C[SZ];
  int N;
  void init(int _n) { N = _n; }
  inline int lowbit(int x) { return x & -x; }
  inline void add(int x, int d) { while (x <= N) C[x] += d, x += lowbit(x); }
  inline LL sum(int x) {
    LL ret = 0;
    while (x) ret += C[x], x -= lowbit(x);
    return ret;
  }
};
struct Rain { int l, r, a; };
const int NN = 3e5 + 8;
Rain Rs[NN];
vector<int> St[NN]; // 每个国家的空间站
int N, M, Ans[NN], P[NN];
BIT<NN> S;
inline void apply(const Rain& q, bool revert = false) {
  int x = q.a, l = q.l, r = q.r;
  if (revert) x = -x;
  if (l <= r) S.add(l, x), S.add(r + 1, -x); // 区间加单点询问用BIT差分实现
  else S.add(l, x), S.add(M + 1, -x), S.add(1, x), S.add(r + 1, -x); // 拆成两个区间
}
// C中的每个国家的查询结果进行二分，目标答案区间是[al, ar]
void solve(const vector<int>& C, int l, int r) {
  if (C.empty()) return;
  if (l == r) { // 答案的目标区间确定了
    for (int c : C) Ans[c] = l;
    return;
  }
  int m = (l + r) / 2;
  _rep(ai, l, m) apply(Rs[ai]); // 看看[l,m]中的下的雨够不够
  vector<int> LC, RC;
  for (int c : C) { // 每个国家都看看
    int &p = P[c];
    LL x = 0;
    for (int s : St[c]) if ((x += S.sum(s)) >= p) break; // 收集够了?
    if (p <= x) LC.push_back(c); // 答案在[l,m]中，国家分到左边
    else p -= x, RC.push_back(c); // 答案在[m+1,r]中，国家分到右边
  }
  _rep(ai, l, m) apply(Rs[ai], true); // 看看[l,m]中的下的雨够不够-还原
  solve(LC, l, m), solve(RC, m + 1, r); //更改顺序，整体二分
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> N >> M, S.init(M + 2);
  int qc, x;
  vector<int> C;
  _rep(i, 1, M) cin >> x, St[x].push_back(i);
  _rep(i, 1, N) cin >> P[i], C.push_back(i);
  cin >> qc;
  _rep(i, 1, qc) cin >> Rs[i].l >> Rs[i].r >> Rs[i].a; // 流星雨下到[l, r]，雨量a
  solve(C, 1, qc + 1);
  _rep(i, 1, N) {
    if (Ans[i] <= qc) cout << Ans[i] << endl;
    else cout << "NIE" << endl;
  }
  return 0;
}
// 25024499   2019-12-07 17:50:24   Feng Chen Meteors accepted  0.92  19M   CPP14