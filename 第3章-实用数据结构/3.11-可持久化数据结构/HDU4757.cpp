// 例题55  树上异或（Tree, ACM/ICPC 2013南京在线赛, HDU4757）
// HDU4757
#include <bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for( int i=(a); i<(int)(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(int)(b); ++i)
const int MAXH = 16, NN = 1e5 + 8, MM = NN * 32;
int A[NN], TC, Ver[NN];
vector<int> G[NN];
struct Trie { int ch[2], cnt; };
Trie B[MM]; // Trie内存分配
int newTrie() {
  int c = TC++;
  fill_n(B[c].ch, 2, 0), B[c].cnt = 0;
  return c;
}

int insert(int p, int v, int dep) {
  int np = newTrie();
  Trie &t = B[np], &t0 = B[p];
  t = t0, t.cnt = t0.cnt + 1;
  if (dep >= 0) {
    bool c = v & 1 << dep;
    t.ch[c] = insert(t0.ch[c], v, dep - 1);
  }
  return np;
}

int Fa[NN][MAXH + 1], D[NN]; // LCA
void dfs(int u, int f) {
  Fa[u][0] = f, D[u] = D[f] + 1;
  _rep(i, 1, MAXH) Fa[u][i] = Fa[Fa[u][i - 1]][i - 1];
  Ver[u] = insert(Ver[f], A[u], 15); // A[u] < 2^16
  for (auto v : G[u]) if (v != f) dfs(v, u);
}

int lca(int u, int v) {
  if (D[u] < D[v]) swap(u, v);
  int diff = D[u] - D[v];
  _rep(h, 0, MAXH) if (diff & (1 << h)) u = Fa[u][h];
  if (u == v) return u;
  for (int h = MAXH; h >= 0; h--)
    if (Fa[u][h] != Fa[v][h]) u = Fa[u][h], v = Fa[v][h];
  return Fa[u][0];
}
int query(int u, int v, int x) {
  int ans = 0, d = lca(u, v), ru = Ver[u], rv = Ver[v], rd = Ver[d];
  for (int i = 15; i >= 0; i--) { // x < 2^16，从高位到低位遍历
    bool f = !(x & 1 << i);
    const Trie &tu = B[ru], &tv = B[rv], &td = B[rd];
    if (B[tu.ch[f]].cnt + B[tv.ch[f]].cnt > B[td.ch[f]].cnt * 2)
      ans |= 1 << i;
    else
      f = !f;
    ru = tu.ch[f], rv = tv.ch[f], rd = td.ch[f];
  }
  return max(ans, x ^ A[d]);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  for (int n, m, u, v, x; cin >> n >> m; ) {
    for (int i = 1; i <= n; i++) cin >> A[i], G[i].clear();
    for (int i = 1; i < n; i++)
      cin >> u >> v, G[u].push_back(v), G[v].push_back(u);
    Ver[0] = TC = 0, newTrie(), dfs(1, 0);
    while (m--)
      cin >> u >> v >> x, printf("%d\n", query(u, v, x));
  }
}
// 32535416 2020-02-19 16:52:41 Accepted  4757  1825MS  38120K  2045 B  G++