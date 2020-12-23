// 例题23 不同的子串（New Distinct Substrings, SPOJ SUBST1）
// 陈锋
#include <bits/stdc++.h>
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
typedef long long LL;
using namespace std;

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
    return;
  }
  inline void build(char* s) { while (*s) insert(*s++); }
};

const int NN = 5e4 + 4;
Suffix_Automaton<NN * 2> sam;
char S[NN];
LL F[NN * 2];

LL dpF(int v) {
  LL &f = F[v];
  if (f != -1) return f;
  f = 1;
  const auto& E = sam.next[v];
  if (E.empty()) return f = 1;
  for (const auto& p : E) f += dpF(p.second);
  return f;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", S);
    sam.init(), sam.build(S);
    fill_n(F, NN * 2, -1);
    printf("%lld\n", dpF(0) - 1);
  }
}
// 24466280 2019-09-26 14:59:33 Feng Chen New Distinct Substrings accepted 0.15  17M CPP14