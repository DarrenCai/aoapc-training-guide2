// 例题29 优势人群（Efficient Solutions, UVa 11020）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Point {
  int x, y;
  bool operator<(const Point& p2) const {
    if (x != p2.x) return x < p2.x;
    return y < p2.y;
  }
};

int main() {
  int T;
  scanf("%d", &T);
  for (int n, x, y, t = 1; t <= T; t++) {
    scanf("%d", &n);
    if (t > 1) puts("");
    printf("Case #%d:\n", t);
    multiset<Point> s;
    for (int i = 0, x, y; i < n; i++) {
      scanf("%d%d", &x, &y);
      Point p = {x, y};
      multiset<Point>::iterator it = s.lower_bound(p);
      if (it == s.begin() || (--it)->y > p.y) {
        s.insert(p), it = s.upper_bound(p);
        while (it != s.end() && it->y >= p.y) s.erase(it++);
      }
      printf("%lu\n", s.size());
    }
  }
  return 0;
}
// Accepted 40ms 880 C++ 5.3.0 2020-12-13 21:48:28 25843791