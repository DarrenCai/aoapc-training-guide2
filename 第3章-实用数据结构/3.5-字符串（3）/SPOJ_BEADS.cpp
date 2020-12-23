// 例题22  最小循环串（Glass Beads, SPOJ BEADS）
// 陈锋
#include <bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for( int i=(a); i<(int)(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(int)(b); ++i)

template<int SZ, int SIG = 32>
struct Suffix_Automaton {
  int link[SZ], len[SZ], last, sz;
  map<char, int> next[SZ];
  inline void init() { sz = 0, last = new_node(); }
  inline int new_node() {
    assert(sz + 1 < SZ);
    int nd = sz++;
    next[nd].clear(), link[nd] = -1, len[nd] = 0;
    return nd;
  }
  inline void insert(char x) {
    int p = last, cur = new_node();
    len[last = cur] = len[p] + 1;
    while (p != -1 && !next[p].count(x))
      next[p][x] = cur, p = link[p];
    if (p == -1) {
      link[cur] = 0;
      return;
    }
    int q = next[p][x];
    if (len[p] + 1 == len[q]) {
      link[cur] = q;
      return;
    }
    int nq = new_node();
    next[nq] = next[q];
    link[nq] = link[q], len[nq] = len[p] + 1, link[cur] = link[q] = nq;
    while (p >= 0 && next[p][x] == q) next[p][x] = nq, p = link[p];
  }
  inline void build(char* s) { while (*s) insert(*s++); }
};

typedef long long LL;
const int NN = 10000 + 4;
char S[NN];
Suffix_Automaton<NN * 4> sam;
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", S);
    sam.init(), sam.build(S), sam.build(S);
    int p = 0, N = strlen(S);
    for (int i = 0; i < N; i++)
      p = sam.next[p].begin()->second;
    printf("%d\n", sam.len[p] - N + 1);
  }
  return 0;
}
// 2594177 Glass Beads Accepted  C++11 0.452 2019-09-26 04:30:13