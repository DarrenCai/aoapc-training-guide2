// 例题38 闪电的能量（Lightning Energy Report, ACM/ICPC Jakarta2010, UVa1674）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
typedef long long LL;

const int MAXN = 65536;
struct SegTree {
  int addv[MAXN * 4], N;
  void update(int o, int L, int R, int qL, int qR, int val) {
    if (qL <= L && R <= qR) {
      addv[o] += val;  //区间加上val
      return;
    }
    int M = (L + R) / 2;
    if (qL <= M) update(o << 1, L, M, qL, qR, val);         //覆盖左区间
    if (M < qR) update(o << 1 | 1, M + 1, R, qL, qR, val);  //覆盖右区间
  }

  void add(int qL, int qR, int val) { update(1, 1, N, qL, qR, val); }

  void init(int o, int L, int R) {  //初始化线段树
    addv[o] = 0;
    if (L == R) return;
    int M = (L + R) / 2;
    init(o << 1, L, M), init(o << 1 | 1, M + 1, R);
  }

  int query(int o, int L, int R, int qv, int val) {
    if (L == R) return val + addv[o];  //找到答案并且将答案返回
    int M = (L + R) >> 1;
    if (qv <= M) return query(o << 1, L, M, qv, val + addv[o]);  //答案在左区间
    return query(o << 1 | 1, M + 1, R, qv, val + addv[o]);  //答案在右区间
  }
};
// Fa[i]为i的父节点,HcHead[i]为i所在重链头,HSon[i]:i重儿子,SZ[i]:子树体积,ID[i]:i在线段树中序号
int Fa[MAXN], HcHead[MAXN], Depth[MAXN], HSon[MAXN], SZ[MAXN], ID[MAXN], intSz;

SegTree ST;
vector<int> G[MAXN];  //存储图
int dfs(int u, int fa) {  //第一次dfs, 得到每个节点的重儿子, 深度, 和父节点
  SZ[u] = 1, Fa[u] = fa, HSon[u] = 0, Depth[u] = Depth[fa] + 1;
  for (auto v : G[u]) {
    if (v == fa) continue;
    SZ[u] += dfs(v, u);
    if (SZ[v] > SZ[HSon[u]]) HSon[u] = v;  //重儿子为体积最大的子树
  }
  return SZ[u];
}
void hld(int u, int fa, int x) {  // 得到节点在线段树中标号及重链的标号
  ID[u] = ++intSz, HcHead[u] = x;  // 重链的标号为该重链最顶端的节点
  if (HSon[u])  // 先处理重链，保证剖分完之后每条重链中的标号是连续的
    hld(HSon[u], u, x);
  for (auto v : G[u])
    if (v != fa && v != HSon[u]) hld(v, u, v);
}

void addPath(int u, int v, int w) {
  while (true) {
    int hu = HcHead[u], hv = HcHead[v];
    if (hu == hv) break;  // 直到两点位于同一条重链才停止
    if (Depth[hu] < Depth[hv]) swap(u, v), swap(hu, hv);  // 更新h→head()
    ST.add(ID[hu], ID[u], w), u = Fa[hu];
  }
  if (Depth[u] < Depth[v]) swap(u, v);
  ST.add(ID[v], ID[u], w);  // 更新u->v
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  cin >> T;
  for (int kase = 1, Q, N; kase <= T; kase++) {
    cin >> N;
    assert(N < MAXN);
    ST.N = N, ST.init(1, 1, N);
    for (int i = 1; i <= N; i++) G[i].clear();
    SZ[0] = 0, Depth[1] = 0;
    for (int i = 1, u, v; i < N; i++) {
      cin >> u >> v, u++, v++;
      G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 1);
    intSz = 0;
    hld(1, 1, 1);
    cin >> Q;
    for (int i = 0, u, v, w; i < Q; i++) {
      cin >> u >> v >> w, u++, v++;
      addPath(u, v, w);
    }
    printf("Case #%d:\n", kase);
    for (int i = 1; i <= N; i++) printf("%d\n", ST.query(1, 1, N, ID[i], 0));
  }
  return 0;
}
// Accepted 140ms 2976 C++5.3.02020-12-1322:18:36 25843914