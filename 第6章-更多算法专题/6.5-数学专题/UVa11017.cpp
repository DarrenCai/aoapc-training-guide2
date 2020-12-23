// UVa11017 A Greener World
// Rujia Liu
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long LL;

const double PI = acos(-1.0);

struct Point {
  int x, y;
  Point(int x = 0, int y = 0) : x(x), y(y) {}
};

typedef Point Vector;

Vector operator+(const Vector& A, const Vector& B) {
  return Vector(A.x + B.x, A.y + B.y);
}
Vector operator-(const Point& A, const Point& B) {
  return Vector(A.x - B.x, A.y - B.y);
}
double Cross(const Vector& A, const Vector& B) {
  return (LL)A.x * B.y - (LL)A.y * B.x;
}

LL PolygonArea2(const vector<Point>& p) {
  int n = p.size();
  LL area2 = 0;
  for (int i = 1; i < n - 1; i++) area2 += Cross(p[i] - p[0], p[i + 1] - p[0]);
  return abs(area2);
}

inline int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

// 线段a-b上的格点数。不包含a和b。设参数t = b/d
// 则d必须是b.x-a.x和b.y-a.y的公约数，且0<b<d,
// 减1因为要排除端点，因此0和d都不能做分子
LL count_on_segment(const Point& a, const Point& b) {
  return gcd(abs(b.x - a.x), abs(b.y - a.y)) - 1;
}

// Pick's Theorem: A = I + B/2 - 1 => I = A - B/2 + 1
LL count_inside_polygon(const vector<Point>& poly) {
  int n = poly.size();
  LL A2 = PolygonArea2(poly);
  int B = n;  // 多边形的顶点
  for (int i = 0; i < n; i++) B += count_on_segment(poly[i], poly[(i + 1) % n]);
  return (A2 - B) / 2 + 1;
}

// 计算内部的、x和y的小数部分都是0.5的点
LL count(const vector<Point>& poly) {
  vector<Point> poly2;
  for (int i = 0; i < poly.size(); i++)  // 旋转45度后的稠密网格坐标
    poly2.push_back(Point(poly[i].x - poly[i].y, poly[i].x + poly[i].y));
  return count_inside_polygon(poly2) - count_inside_polygon(poly);
}

int main() {
  // theta和d仅仅用来算面积
  for (int d, theta, N, x, y; scanf("%d%d%d", &d, &theta, &N) == 3 && d;) {
    vector<Point> poly;
    for (int i = 0; i < N; i++)
      scanf("%d%d", &x, &y), poly.push_back(Point(x, y));
    LL area2 = PolygonArea2(poly);
    printf("%lld %.0lf\n", count(poly),
           sin((double)theta / 180 * PI) * d * d * area2 / 2.0);
  }
  return 0;
}
// Accepted 1963 C++5.3.0 2020-12-1222:36:42|□25840418