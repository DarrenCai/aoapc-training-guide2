// 例题45  动态逆序对（CQOI2011）
// 陈锋
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
template <int SZ>
struct BIT {
  int C[SZ], N;
  inline int lowbit(int x) { return x & -x; }
  void add(int x, int v) {
    while (x <= N) C[x] += v, x += lowbit(x);
  }
  int sum(int x) {
    int r = 0;
    while (x) r += C[x], x -= lowbit(x);
    return r;
  }
};
const int NN = 1e5 + 8;
BIT<NN> S;
struct OP {
  int id, p, v;  //第id个命令，在位置p插入v
  bool operator<(const OP &b) { return p > b.p; }
} O[NN], T[NN];
int N, M, A[NN], Pos[NN], Vis[NN];
LL Ans[NN];  //第id个命令插入x之后增加多少个逆序对
void solve(int l, int r) {  // 按照插入位置从大到小排序
  if (l == r) return;
  int m = (l + r) / 2, l1 = l, l2 = m + 1;
  for (int i = l; i <= r; i++) {  //情况1
    const OP &o = O[i];
    if (o.id <= m) S.add(o.v, 1);  // id ∈ [l,m]
    else Ans[o.id] += S.sum(o.v);  // id ∈ [m + 1,r]
  }
  for (int i = l; i <= r; i++)
    if (O[i].id <= m) S.add(O[i].v, -1);  //还原BIT
  for (int i = r; i >= l; --i) {          //情况2
    const OP &o = O[i];
    if (o.id <= m)
      S.add(N - o.v + 1, 1);  // id∈[l,m],记录插入的N–v+1≥v的元素个数
    else
      Ans[o.id] += S.sum(N - o.v + 1);
    // id ∈ [m + 1,r],v映射到N – v + 1,比如N -> 1,N – 1 -> 2
  }

  for (int i = l; i <= r; i++) {  //分治：把id∈[l,m]，[m+1,r]的操作分别放两边
    const OP &o = O[i];
    if (o.id <= m) T[l1++] = o, S.add(N - o.v + 1, -1);  //还原BIT
    else T[l2++] = o;
  }
  copy(T + l, T + r + 1, O + l);
  solve(l, m), solve(m + 1, r);
}

int main() {
  cin >> N >> M;
  int id = N, qc = M;
  S.N = N;
  for (int i = 1; i <= N; ++i) cin >> A[i], Pos[A[i]] = i;
  for (int i = 1; i <= M; ++i) {
    OP &q = O[i];
    cin >> q.v, Vis[q.p = Pos[q.v]] = true, q.id = id--;
  }
  for (int i = 1; i <= N; ++i) {
    if (Vis[i]) continue;
    O[++qc] = {id--, i, A[i]};
  }
  sort(O + 1, O + 1 + N);  //根据插入位置递减排序
  solve(1, N);
  for (int i = 1; i <= N; ++i) Ans[i] += Ans[i - 1];
  _for(i, 0, M) cout << Ans[N - i] << endl;
  return 0;
}
// 46047579 [CQOI2011]动态逆序对 答案正确 100 201 5604 2010 C++ 2020-12-13 22:59:28