// UVa11297 - Census
// 陈锋
#include<stdio.h>
#include<algorithm>
#include<cstring>
using namespace std;
const int NN = 508, INF = 1e9;
struct SegTree2D {
  struct Node {
    int Max, Min;
    void update(const Node& nd) {
      Max = max(Max, nd.Max), Min = min(Min, nd.Min);
    }
  } NS[NN][NN * 4]; //第一维表示是用矩阵的第几行建立的线段树

  Node qAns;
  void maintain(int c, int o) {
    Node& nd = NS[c][o], ld = NS[c][2 * o], rd = NS[c][2 * o + 1];
    nd.Max = max(ld.Max, rd.Max), nd.Min = min(ld.Min, rd.Min);
  }

  void build(int c, int o, int l, int r) {
    Node& nd = NS[c][o];
    if (l == r) {
      scanf("%d", &nd.Min), nd.Max = nd.Min;
      return ;
    }
    int mid = (l + r) / 2, lc = o * 2, rc = o * 2 + 1;
    build(c, lc, l, mid), build(c, rc, mid + 1, r);
    maintain(c, o);
  }

  void query(int c, int o, int l, int r, int qL, int qR) {
    if (l == qL && r == qR) {
      qAns.update(NS[c][o]);
      return;
    }
    int qM = (qL + qR) / 2, lc = o * 2, rc = o * 2 + 1;
    if (qM >= r) query(c, lc, l, r, qL, qM);
    else if (qM < l) query(c, rc, l, r, qM + 1, qR);
    else query(c, lc, l, qM, qL, qM), query(c, rc, qM + 1, r, qM + 1, qR);
  }

  void modify(int c, int x, int val, int o, int l, int r) {
    Node& nd = NS[c][o];
    if (l == r && l == x) {
      nd.Max = nd.Min = val;
      return ;
    }
    int m = (l + r) / 2, lc = o * 2, rc = o * 2 + 1;
    if (m >= x) modify(c, x, val, lc, l, m);
    else if (m < x) modify(c, x, val, rc,  m + 1, r);
    maintain(c, o);
  }
};
SegTree2D ST;
int main() {
  char op[10];
  for (int m, n, x1, y1, x2, y2, v; scanf("%d", &n) != EOF;) {
    for (int x = 1; x <= n; x++) ST.build(x, 1, 1, n);
    scanf("%d", &m);
    while (m--) {
      scanf("%s", op);
      if (op[0] == 'q') {
        ST.qAns.Max = -INF, ST.qAns.Min = INF;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        for (int x = x1; x <= x2; x++) ST.query(x, 1, y1, y2, 1, n);
        printf("%d %d\n", ST.qAns.Max, ST.qAns.Min);
      }
      if (op[0] == 'c')
        scanf("%d%d%d", &x1, &y1, &v), ST.modify(x1, y1, v, 1, 1, n);
    }
  }
  return 0;
}
// 25858184 11297 Census  Accepted  C++ 0.430 2020-12-17 09:28:06