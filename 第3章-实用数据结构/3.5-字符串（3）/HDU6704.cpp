// 例题28  第K次出现（Kth-occurrence, HDU6704, CCPC 2019网络选拔赛）
// 陈锋
#include<bits/stdc++.h>
using namespace std;
const int NN = 1e6 + 10;
template<int SZ>
struct WSegTree { // 动态权值线段树
  int sz, ls[SZ * 4], rs[SZ * 4], sum[SZ * 4];
  void init() { sz = 0; }
  int maintain(int u) { sum[u] = sum[ls[u]] + sum[rs[u]]; return u; }
  int new_node() {
    ++sz;
    sum[sz] = ls[sz] = rs[sz] = 0;
    return sz;
  }

  void insert(int& u, int l, int r, int k) { // add a k in u([l, r])
    if (u == 0) u = new_node();
    if (l == r) {
      assert(l <= k && k <= r);
      sum[u]++;
      return;
    }
    int m = (l + r) / 2;
    if (k <= m) insert(ls[u], l, m, k);
    else insert(rs[u], m + 1, r, k);
    maintain(u);
  }

  int merge(int x, int y) { // 权值线段树合并
    if (x == 0 || y == 0) return x + y;
    int p = new_node();
    ls[p] = merge(ls[x], ls[y]), rs[p] = merge(rs[x], rs[y]);
    return maintain(p);
  }

  int kth(int u, int l, int r, int k) {
    if (l == r) return l; // node u([l,r]), 查询第k小
    int m = (l + r) / 2, lc = ls[u], rc = rs[u];
    if (k <= sum[lc]) return kth(lc, l, m, k);
    if (k <= sum[u]) return kth(rc, m + 1, r, k - sum[lc]);
    return -1;
  }
};
struct Edge { int to, next; };
template<int SZ>
struct SAM {
  WSegTree<SZ> st;
  int sz, last, len[SZ], link[SZ], ch[SZ][30], end_pos[SZ];
  int seg_root[SZ], fa[SZ][30], ecnt, EHead[SZ];
  Edge E[SZ * 2];

  void init() {
    last = 1, ecnt = 0, sz = 0;
    new_stat(), st.init();
  }

  int new_stat() {
    int q = ++sz;
    EHead[q] = 0, len[q] = 0, link[q] = 0, seg_root[q] = 0;
    fill_n(ch[q], 30, 0);
    return q;
  }

  void insert(int i, int c, int n) {
    int cur = new_stat(), p = last;
    end_pos[i] = cur, len[cur] = i;
    for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
    if (!p)
      link[cur] = 1;
    else {
      int q = ch[p][c];
      if (len[q] == len[p] + 1) link[cur] = q;
      else {
        int nq = new_stat();
        link[nq] = link[q], len[nq] = len[p] + 1;
        for (; p && ch[p][c] == q; p = link[p]) ch[p][c] = nq;
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        link[q] = link[cur] = nq;
      }
    }
    last = cur;
    st.insert(seg_root[cur], 1, n, i);
  }

  // 后缀树结构维护->倍增逻辑
  void add_edge(int x, int y) { E[++ecnt] = {y, EHead[x]}, EHead[x] = ecnt; }

  void dfs(int u) {
    for (int i = 1; i <= 20; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = EHead[u]; i; i = E[i].next) {
      int v = E[i].to;
      fa[v][0] = u, dfs(v);
      seg_root[u] = st.merge(seg_root[u], seg_root[v]);
    }
  }

  void build() {
    for (int i = 2; i <= sz; ++i) add_edge(link[i], i);
    dfs(1);
  }

  int kth(int l, int r, int k, int n) {
    int u = end_pos[r];
    for (int i = 20; i >= 0; --i) { // 倍增找S[l, r]对应的点
      int p = fa[u][i];
      if (l + len[p] - 1 >= r) u = p;
    }
    int ans = st.kth(seg_root[u], 1, n, k);
    return (ans == -1) ? ans : ans - (r - l);
  }
};

SAM<NN> sam;
char a[NN];
int main() {
  int N, T, q, l, r, k;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &q), scanf("%s", a + 1), sam.init();
    for (int i = 1; i <= N; ++i) sam.insert(i, a[i] - 'a' + 1, N);
    sam.build();
    while (q--) {
      scanf("%d%d%d", &l, &r, &k);
      printf("%d\n", sam.kth(l, r, k, N));
    }
  }
  return 0;
}
// Accepted 1684ms 92092kB 3271 G++2019-12-09 21:34:42 31813560