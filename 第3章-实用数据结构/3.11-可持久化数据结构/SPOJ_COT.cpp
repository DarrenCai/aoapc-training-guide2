// 例题54  树上计数（Count on a tree, SPOJ COT）
// 陈锋
#include <bits/stdc++.h>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))

const int MAXN = 100000 + 4, LN = 19;
int W[MAXN], RM[MAXN], maxw = 0;
map<int, int> WI;

vector<int> G[MAXN]; // 树结构以及LCA
int N, L, Tin[MAXN], Tout[MAXN], UP[MAXN][18], timer;

/* 主席树 */
struct Node;
typedef Node *PNode;
struct Node {
  int count;
  Node *left, *right;
  Node(int count, Node *left, Node *right)
    : count(count), left(left), right(right) {}
  Node *insert(int l, int r, int w);
};

PNode Null = new Node(0, nullptr, nullptr);
PNode Node::insert(int l, int r, int w) {
  if (l <= w && w < r) {  // need a new Node
    if (l + 1 == r) return new Node(count + 1, Null, Null);
    int m = (l + r) / 2;
    return new Node(count + 1, left->insert(l, m, w), right->insert(m, r, w));
  }
  return this;
}
PNode VER[MAXN];

// LCA
void dfs(int u, int fa) {
  Tin[u] = ++timer, UP[u][0] = fa;
  for (int i = 1; i < L; i++) UP[u][i] = UP[UP[u][i - 1]][i - 1];
  VER[u] = (u == 0 ? Null : VER[fa])->insert(0, maxw, WI[W[u]]);
  for (auto v : G[u]) if (v != fa) dfs(v, u);
  Tout[u] = ++timer;
}

bool isAncestor(int u, int v) { return Tin[u] <= Tin[v] && Tout[u] >= Tout[v]; }

int LCA(int u, int v) {
  if (isAncestor(u, v)) return u;
  if (isAncestor(v, u)) return v;
  for (int i = L; i >= 0; --i)
    if (!isAncestor(UP[u][i], v)) u = UP[u][i];
  return UP[u][0];
}

// 主席树查询 u,v,lca(u,v), pa(lca), get kth in [l,r)
int query(PNode pu, PNode pv, PNode pd, PNode ppd, int l, int r, int k) {
  if (l + 1 == r) return l;
  int count = pu->left->count + pv->left->count - pd->left->count -
              ppd->left->count,
              m = (l + r) / 2;
  if (count >= k)
    return query(pu->left, pv->left, pd->left, ppd->left, l, m, k);
  return query(pu->right, pv->right, pd->right, ppd->right, m, r, k - count);
}

int main() {
  int M;
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> N >> M;
  L = ceil(log2(N));
  _for(i, 0, N) cin >> W[i], WI[W[i]];
  maxw = 0;
  for (auto it = WI.begin(); it != WI.end(); it++, maxw++)
    it->second = maxw, RM[maxw] = it->first;

  int u, v, k;
  _for(i, 0, N - 1) {
    cin >> u >> v, u--, v--;
    G[u].push_back(v), G[v].push_back(u);
  }
  Null->left = Null->right = Null;
  timer = 0;
  dfs(0, 0);
  while (M--) {
    cin >> u >> v >> k, u--, v--;
    int d = LCA(u, v),
        ans = query(VER[u], VER[v], VER[d],
                    (d == 0 ? Null : VER[UP[d][0]]), 0, maxw, k);
    cout << RM[ans] << endl;
  }
  return 0;
}
// 27147320	2020-12-23 07:33:54	Feng Chen	Count on a tree	accepted 4.03	82M	CPP