// 例题10  快速矩阵操作（Fast Matrix Operations, UVa 11992）
// 陈锋
#include <bits/stdc++.h>

using namespace std;

const int MAXC = 1e6 + 4, INF = 1e9;
struct NodeInfo {
  int minv, maxv, sumv;
};
NodeInfo operator+(const NodeInfo &n1, const NodeInfo &n2) {
  return {min(n1.minv, n2.minv), max(n1.maxv, n2.maxv), n1.sumv + n2.sumv};
}

struct IntervalTree {
  NodeInfo nodes[MAXC];
  int setv[MAXC], addv[MAXC], qL, qR;
  bitset<MAXC> isSet;
  inline void setFlag(int o, int v) { setv[o] = v, isSet.set(o), addv[o] = 0; }
  void init(int n) {
    int sz = n * 2 + 2;
    fill_n(addv, sz, 0);
    isSet.reset(), isSet.set(1);
    memset(nodes, 0, sizeof(NodeInfo) * sz);
  }

  inline void maintain(int o, int L, int R) {  // 维护信息
    int lc = o * 2, rc = o * 2 + 1, a = addv[o], s = setv[o];
    NodeInfo &nd = nodes[o], &li = nodes[lc], &ri = nodes[rc];
    if (R > L) nd = li + ri;
    if (isSet[o]) nd = {s, s, s * (R - L + 1)};
    if (a) nd.minv += a, nd.maxv += a, nd.sumv += a * (R - L + 1);
  }

  inline void pushdown(int o) {  // 标记传递
    int lc = o * 2, rc = o * 2 + 1;
    if (isSet[o])
      setFlag(lc, setv[o]), setFlag(rc, setv[o]), isSet.reset(o); // 清除标记
    if (addv[o])
      addv[lc] += addv[o], addv[rc] += addv[o], addv[o] = 0; // 清除标记
  }

  void update(int o, int L, int R, int op, int v) {  // op(1:add, 2:set)
    int lc = o * 2, rc = o * 2 + 1, M = L + (R - L) / 2;
    if (qL <= L && qR >= R) {  // 标记修改
      if (op == 1) addv[o] += v;  // add
      else setFlag(o, v);  // set
    } else {
      pushdown(o);
      if (qL <= M) update(lc, L, M, op, v);
      else maintain(lc, L, M);
      if (qR > M) update(rc, M + 1, R, op, v);
      else maintain(rc, M + 1, R);
    }
    maintain(o, L, R);
  }

  NodeInfo query(int o, int L, int R) {
    int lc = o * 2, rc = o * 2 + 1, M = L + (R - L) / 2;
    maintain(o, L, R);
    if (qL <= L && qR >= R) return nodes[o];

    pushdown(o);
    NodeInfo li = {INF, -INF, 0}, ri = {INF, -INF, 0};
    if (qL <= M) li = query(lc, L, M);
    else maintain(lc, L, M);
    if (qR > M) ri = query(rc, M + 1, R);
    else maintain(rc, M + 1, R);
    return li + ri;
  }
};

const int maxr = 20 + 5;
IntervalTree tree[maxr];
int main() {
  for (int r, c, m; scanf("%d%d%d", &r, &c, &m) == 3;) {
    for (int x = 1; x <= r; x++) tree[x].init(c);
    for (int i = 0, op, x1, y1, x2, y2, v; i < m; i++) {
      scanf("%d%d%d%d%d", &op, &x1, &y1, &x2, &y2);
      if (op < 3) {
        scanf("%d", &v);
        for (int x = x1; x <= x2; x++) {
          IntervalTree &tx = tree[x];
          tx.qL = y1, tx.qR = y2, tx.update(1, 1, c, op, v);
        }
      } else {
        NodeInfo gi = {INF, -INF, 0};
        for (int x = x1; x <= x2; x++) {
          IntervalTree &tx = tree[x];
          tx.qL = y1, tx.qR = y2, gi = gi + tx.query(1, 1, c);
        }
        printf("%d %d %d\n", gi.sumv, gi.minv, gi.maxv);
      }
    }
  }
  return 0;
}
// Accepted 550ms 2968 C++5.3.02020-12-1321:05:39 25843628