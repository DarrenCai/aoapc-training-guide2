// 例题39 软件包管理器（NOI 2015）牛客NC 17882）
// 陈锋
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

template <typename T, int SZ>
struct SegTree {
  struct Node {
    T sumv, setv;
    bool hasSet;
    void setVal(const T& val, int L, int R) {
      setv = val, hasSet = true, sumv = (R - L + 1) * setv;
    }
  };  // sumv: 最新的和；setv: 最新的set标记(子孙不受影响)
  Node NS[SZ];
  int N;
  void init(int _n) {
    N = _n;
    assert((1 << ((int)ceil(log2(N)))) < SZ);
  }

  void pushdown(int o, int L, int R) {
    Node& nd = NS[o];
    if (!nd.hasSet) return;
    int lc = 2 * o, rc = 2 * o + 1, M = (L + R) / 2;
    NS[lc].setVal(nd.setv, L, M), NS[rc].setVal(nd.setv, M + 1, R);
    nd.hasSet = false;
  }

  void setV(int l, int r, const T& v) { update(1, 1, N, v, l, r); }
  void update(int o, int L, int R, const T& v, int qL, int qR) {
    if (qL <= L && qR >= R) {
      NS[o].setVal(v, L, R);
      return;
    }
    int lc = 2 * o, rc = 2 * o + 1, M = (L + R) / 2;
    pushdown(o, L, R);
    if (qL <= M) update(lc, L, M, v, qL, qR);
    if (qR > M) update(rc, M + 1, R, v, qL, qR);
    NS[o].sumv = NS[lc].sumv + NS[rc].sumv;
  }
  T querysum(int l, int r) { return query(1, 1, N, l, r); }
  T query(int o, int L, int R, int qL, int qR) {
    if (qL <= L && qR >= R) return NS[o].sumv;
    pushdown(o, L, R);
    int lc = 2 * o, rc = 2 * o + 1, M = (L + R) / 2;
    T s = 0;
    if (qL <= M) s += query(lc, L, M, qL, qR);
    if (qR > M) s += query(rc, M + 1, R, qL, qR);
    return s;
  }
};

template <int SZ = 1004>
struct HLD {  //树链剖分
  int N, Fa[SZ], HcHead[SZ], Dep[SZ], HcTail[SZ], HSon[SZ], Usz[SZ];
  int ID[SZ], segSz;
  vector<int> G[SZ];
  void init(int _n) {
    segSz = 0;
    N = _n;
    assert(_n < SZ);
  }
  int dfs(int u, int fa) {  //返回子树体积
    int &h = HSon[u], &sz = Usz[u];
    sz = 1, Fa[u] = fa, h = 0, Dep[u] = Dep[fa] + 1;
    for (size_t i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
      if (v == fa) continue;
      sz += dfs(v, u);
      if (Usz[v] > Usz[h]) h = v;  //体积最大的子树
    }
    return sz;  // dfs得到重儿子，深度，父节点
  }
  void hld(int u, int fa, int head) {  //轻重剖分
    ID[u] = ++segSz, HcHead[u] = head;
    if (HSon[u]) {
      hld(HSon[u], u, head);  //重链向下扩展
      for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];  //轻儿子新开重链
        if (v != fa && v != HSon[u]) hld(v, u, v);
      }
      return;
    }
    HcTail[head] = u;
  }
  void addEdge(int u, int v) { G[u].push_back(v); }
  void build(int root = 1) { dfs(root, 0), hld(root, 0, root); }
};

const int NN = 1e5 + 8;
SegTree<int, NN * 3> St;
HLD<NN> H;
const int Root = 1;
int queryRootPathSum(int u) {  //查询u到树根路径上所有点的权值之和
  int ans = 0;
  while (true) {
    int hu = H.HcHead[u];
    ans += St.querysum(H.ID[hu], H.ID[u]);
    if (hu == Root) break;
    u = H.Fa[hu];
  }
  return ans;
}
void setRootPath(int u) {  //设置u到树根路径上所有点的权值为1
  while (true) {
    int hu = H.HcHead[u];
    St.setV(H.ID[hu], H.ID[u], 1);
    if (hu == Root) break;
    u = H.Fa[hu];
  }
}
int querySubTreeSum(int u) {  //子树u的所有点权之和，所有点在DFS序中是连续的
  return St.querysum(H.ID[u], H.ID[u] + H.Usz[u] - 1);
}
void clearSubTree(int u) {  //设置子树u的所有点权为0
  St.setV(H.ID[u], H.ID[u] + H.Usz[u] - 1, 0);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int N, Q;
  cin >> N, H.init(N + 1), St.init(N + 1);
  for (int u = 2, p; u <= N; u++) cin >> p, H.addEdge(p + 1, u);
  H.build(Root), cin >> Q;
  string s;
  for (int i = 0, x; i < Q; i++) {
    cin >> s >> x, ++x;
    if (s[0] == 'i') {  //安装 x
      int s0 = queryRootPathSum(x);
      setRootPath(x);
      cout << queryRootPathSum(x) - s0 << endl;
    } else {  //卸载 x
      int s0 = querySubTreeSum(x);
      clearSubTree(x);
      cout << s0 << endl;
    }
  }
  return 0;
}
// 46047267 软件包管理器 答案正确 100 392 12212 3644 C++ 2020-12-13 22:29:46