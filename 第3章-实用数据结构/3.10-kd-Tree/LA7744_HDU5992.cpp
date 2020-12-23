// 例题51  寻找酒店（Finding Hotels, ACM/ICPC 青岛 2016, LA7744/HDU5992
// 陈锋
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
const int NN = 2E5 + 8;
struct Point {
  LL x, y;
  int c, id;
} Ps[NN];
istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y >> p.c; }
bool cmpx(const Point& p1, const Point& p2) { return p1.x < p2.x; }
bool cmpy(const Point& p1, const Point& p2) { return p1.y < p2.y; }
LL dist(const Point& a, const Point& b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
bool Div[NN];  // 每一层的划分方式
void build(int l, int r) {
  if (l > r) return;
  int m = (l + r) / 2;
  Point *pl = Ps + l, *pr = Ps + r + 1;
  pair<Point*, Point*> px = minmax_element(pl, pr, cmpx),
                       py = minmax_element(pl, pr, cmpy);
  Div[m] = px.second->x - px.first->x >= py.second->y - py.first->y;
  nth_element(pl, Ps + m, pr, Div[m] ? cmpx : cmpy);
  build(l, m - 1), build(m + 1, r);
}
// Ps[L,r]中距离p最小的点->id，最小距离min_d。且要求Ps[id].c<p.c
void nearest(int l, int r, const Point& p, LL& min_d, int& id) {
  if (l > r) return;
  int m = (l + r) / 2;
  const Point& pm = Ps[m];
  LL d = dist(p, pm);
  if (pm.c <= p.c) {
    if (d < min_d) min_d = d, id = m;
    else if (d == min_d && pm.id < Ps[id].id) id = m;
  }
  d = Div[m] ? (p.x - pm.x) : (p.y - pm.y);
  if (d <= 0) {
    nearest(l, m - 1, p, min_d, id);
    if (d * d < min_d) nearest(m + 1, r, p, min_d, id);
  } else {
    nearest(m + 1, r, p, min_d, id);
    if (d * d < min_d) nearest(l, m - 1, p, min_d, id);
  }
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int id, n, m, T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> Ps[i], Ps[i].id = i;
    build(1, n);
    Point p;
    while (m--) {
      cin >> p;
      LL min_d = 1LL << 60;
      nearest(1, n, p, min_d, id);
      printf("%lld %lld %d\n", Ps[id].x, Ps[id].y, Ps[id].c);
    }
  }
  return 0;
}
// 32942274 2020-04-02 18:03:46 Accepted  5992  358MS 6344K 1962 B  G++ chenwz