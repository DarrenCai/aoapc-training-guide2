// 例题26  子串计数（Substrings, SPOJ NSUBSTR）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for( int i=(a); i<(int)(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(int)(b); ++i)
typedef long long LL;

template<int SZ, int SIG = 32>
struct Suffix_Automaton {
  int link[SZ], len[SZ], isterminal[SZ], next[SZ][SIG], last, sz;
  inline void init() { sz = 0, last = new_node(); }
  inline int new_node() {
    assert(sz + 1 < SZ);
    int nd = sz++;
    fill_n(next[nd], SIG, 0), link[nd] = -1, len[nd] = 0, isterminal[nd] = 0;
    return nd;
  }
  inline int idx(char c) { return c - 'a'; }
  inline void insert(char c) {
    int p = last, cur = new_node(), x = idx(c);
    len[last = cur] = len[p] + 1, isterminal[cur] = 1;
    while (p != -1 && !next[p][x]) next[p][x] = cur, p = link[p];
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
    copy_n(next[q], SIG, next[nq]);
    link[nq] = link[q], len[nq] = len[p] + 1, link[cur] = link[q] = nq;
    while (p >= 0 && next[p][x] == q) next[p][x] = nq, p = link[p];
  }
  inline void build(const char* s) { while (*s) insert(*s++); }
};

const int NN = 250000 + 4;
vector<int> G[NN * 2];
Suffix_Automaton<NN * 2> sam;
int F[NN];
int dfs(int u) {
  int s = sam.isterminal[u];
  for (auto v : G[u]) s += dfs(v);
  F[sam.len[u]] = max(F[sam.len[u]], s);
  return s;
}

char S[NN];
int main() {
  scanf("%s", S);
  int N = strlen(S);
  sam.init(), sam.build(S);
  _for(u, 1, sam.sz) G[sam.link[u]].push_back(u);
  dfs(0);
  _rep(l, 1, N) printf("%d\n", F[l]);
  return 0;
}
// 24467571 2019-09-26 17:18:19 Feng Chen Substrings  accepted 0.22  70M CPP14