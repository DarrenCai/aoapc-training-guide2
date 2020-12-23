// 例题27  子串之和（str2int, Asia – Tianjin 2012, LA6387/UVa1673）
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
  inline void build(const char* s) { while (*s) insert(*s++); }
};

typedef long long LL;
const int NS = 2e5 + 4, M = 2012;
Suffix_Automaton<NS> sam;
int V[NS], Cnt[NS], Sum[NS];
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  string s;
  int N;
  while (cin >> N && N) {
    sam.init();
    _for(i, 0, N) {
      cin >> s, sam.build(s.c_str());
      if (i != N - 1) sam.insert('9' + 1);
    }
    _for(i, 0, sam.sz) V[i] = i;
    sort(V, V + sam.sz, [](int a, int b) { return sam.len[a] < sam.len[b]; });
    fill_n(Cnt, sam.sz, 0), fill_n(Sum, sam.sz, 0);

    Cnt[0] = 1;
    int ans = 0;
    _for(i, 0, sam.sz) {
      int u = V[i];
      char st = u ? '0' : '1';
      for (char c = st; c <= '9'; ++c)
        if (sam.next[u].count(c)) {
          int v = sam.next[u][c];
          (Cnt[v] += Cnt[u]) %= M;
          (Sum[v] += Sum[u] * 10 + (c - '0') * Cnt[u]) %= M;
        }
      (ans += Sum[u]) %= M;
    }
    cout << ans << endl;
  }
  return 0;
}
// 25877523	1673	str2int	Accepted	C++	0.410	2020-12-23 05:48:53