// 例题25  转世（Reincarnation HDU4622）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for( int i=(a); i<(int)(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(int)(b); ++i)
typedef long long LL;

template<int SZ, int SIG = 32>
struct Suffix_Automaton {
  int link[SZ], len[SZ], isClone[SZ], next[SZ][SIG], last, sz;
  inline void init() { sz = 0, last = new_node(); }
  inline int new_node() {
    assert(sz + 1 < SZ);
    int nd = sz++;
    fill_n(next[nd], SIG, 0), link[nd] = -1, len[nd] = 0, isClone[nd] = 0;
    return nd;
  }
  inline int idx(char c) { return c - 'a'; }
  inline void insert(char c) {
    int p = last, cur = new_node(), x = idx(c);
    len[last = cur] = len[p] + 1;
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
    isClone[nq] = 1, copy_n(next[q], SIG, next[nq]);
    link[nq] = link[q], len[nq] = len[p] + 1, link[cur] = link[q] = nq;
    while (p >= 0 && next[p][x] == q) next[p][x] = nq, p = link[p];
  }
  inline void build(const char* s) { while (*s) insert(*s++); }
};

const int NN = 2000 + 4;
Suffix_Automaton<2 * NN> sam;
int F[NN][NN];

int main() {
  string s;
  ios::sync_with_stdio(false), cin.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> s;
    int N = s.size();
    memset(F, 0, sizeof(F));
    _for(i, 0, N) {
      sam.init();
      _for(j, i, N) {
        sam.insert(s[j]);
        int p = sam.last;
        F[i][j] = F[i][j - 1] + sam.len[p] - sam.len[sam.link[p]];
      }
    }
    int Q, l, r; cin >> Q;
    _for(i, 0, Q) {
      cin >> l >> r;
      cout << F[l - 1][r - 1] << endl;
    }
  }
  return 0;
}
// Accepted 1076ms 18576kB 1780 G++ 2019-09-26 23:54:34