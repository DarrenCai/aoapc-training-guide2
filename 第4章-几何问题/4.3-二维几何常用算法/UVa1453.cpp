// 例题9  正方形（Squares, Seoul 2009, UVa1453）
// 陈锋
#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point(int x = 0, int y = 0) : x(x), y(y) {}
};

typedef Point Vector;
istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y; }
ostream& operator<<(ostream& os, const Point& p) {
  return os << p.x << " " << p.y;
}

Vector operator-(const Point& A, const Point& B) {
  return Vector(A.x - B.x, A.y - B.y);
}
int Cross(const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }
int Dot(const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
int Dist2(const Point& A, const Point& B) {
  return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}
bool operator<(const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}
bool operator==(const Point& p1, const Point& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

vector<Point> ConvexHull(vector<Point>& p) {  // 点集凸包
  sort(p.begin(), p.end());                   // 预处理，删除重复点
  p.erase(unique(p.begin(), p.end()), p.end());

  int n = p.size();
  int m = 0;
  vector<Point> ch(n + 1);
  for (int i = 0; i < n; i++) {
    while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for (int i = n - 2; i >= 0; i--) {
    while (m > k && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) m--;
    ch[m++] = p[i];
  }
  if (n > 1) m--;
  ch.resize(m);
  return ch;
}

int diameter2(vector<Point>& points) {  // 返回点集直径的平方
  vector<Point> p = ConvexHull(points);
  int n = p.size();
  if (n == 1) return 0;
  if (n == 2) return Dist2(p[0], p[1]);
  p.push_back(p[0]);  // 免得取模
  int ans = 0;
  for (int u = 0, v = 1; u < n; u++) {
    for (;;) {  // 一条直线贴住边p[u]-p[u+1]
      // 当Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])时停止旋转
      // 即Cross(p[u+1]-p[u], p[v+1]-p[u]) - Cross(p[u+1]-p[u], p[v]-p[u]) <= 0
      // 根据Cross(A,B) - Cross(A,C) = Cross(A,B-C)
      // 化简得Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
      int diff = Cross(p[u + 1] - p[u], p[v + 1] - p[v]);
      if (diff <= 0) {
        ans = max(ans, Dist2(p[u], p[v]));  // u和v是对踵点
        if (diff == 0)
          ans = max(ans, Dist2(p[u], p[v + 1]));  // diff == 0时u和v+1也是对踵点
        break;
      }
      v = (v + 1) % n;
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  cin >> T;
  for (int t = 0, n; t < T; t++) {
    cin >> n;
    vector<Point> ps;
    for (int i = 0, x, y, w; i < n; i++) {
      cin >> x >> y >> w;
      ps.push_back(Point(x, y)), ps.push_back(Point(x + w, y));
      ps.push_back(Point(x, y + w)), ps.push_back(Point(x + w, y + w));
    }
    printf("%d\n", diameter2(ps));
  }
  return 0;
}
// 25845984 1453 Squares Accepted C++ 0.130 2020-12-14 06:26:23
