// 例题49 D-查询（SPOJ DQUERY）
// 陈锋
#include <bits/stdc++.h>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)

const int NN = 300000 + 4, MM = 200000 + 4, AA = 1000000 + 4;
int A[NN], ANS[MM], N, M, BLOCK;
struct query {
  int L, R, id;
  bool operator<(const query& q) const {
    int lb = L / BLOCK;
    if (lb != q.L / BLOCK) return lb < q.L / BLOCK;
    if (lb % 2) return R < q.R;
    return R > q.R;
  }
};

query Q[MM];
int ans, curL, curR, CNT[AA];
void add(int pos) {
  if (++CNT[A[pos]] == 1) ++ans;
}
void remove(int pos) {
  if (--CNT[A[pos]] == 0) --ans;
}

typedef long long LL;
int main() {
  scanf("%d", &N);
  _rep(i, 1, N) scanf("%d", &A[i]), CNT[A[i]] = 0;
  scanf("%d", &M);
  BLOCK = max((int)ceil((double)N / sqrt(M)), 16);
  _for(i, 0, M) scanf("%d%d", &Q[i].L, &Q[i].R), Q[i].id = i;
  sort(Q, Q + M);
  CNT[A[1]] = 1, ans = 1, curL = 1, curR = 1;
  _for(i, 0, M) {
    while (curL < Q[i].L) remove(curL++);
    while (curL > Q[i].L) add(--curL);
    while (curR < Q[i].R) add(++curR);
    while (curR > Q[i].R) remove(curR--);
    ANS[Q[i].id] = ans;
  }
  _for(i, 0, M) printf("%d\n", ANS[i]);
  return 0;
}
// Accepted 310ms 11264kB 1215 C++(gcc 8.3)2020-12-13 23:10:54 27090670