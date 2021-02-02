// 例题7  飞机场（Airport, UVa 11168）
// 李劲逸,陈锋 - 不用解析几何知识的版本
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-7;

struct Point {
  double x, y;
  Point(double a = 0, double b = 0) : x(a), y(b) {}
};
typedef Point Vector;
istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y; }
ostream& operator<<(ostream& os, const Point& p) { return os << p.x << " " << p.y; }
Vector operator + (const Point& A, const Point& B)
{return Vector(A.x + B.x, A.y + B.y);}
Vector operator - (const Point& A, const Point& B)
{return Vector(A.x - B.x, A.y - B.y);}
bool operator < (const Point& p1, const Point& p2)
{ return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);}
bool operator == (const Point& p1, const Point& p2)
{ return p1.x == p2.x && p1.y == p2.y;}
double Cross(const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }
double Dot(const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }

// 点集凸包， 如果不希望在凸包的边上有输入点，把两个 <= 改成 <
// 如果不介意点集被修改，可以改成传递引用
vector<Point> ConvexHull(vector<Point> p) {
  sort(p.begin(), p.end()); // 预处理，删除重复点
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

double solve(vector<Point> &A) {
  int n = A.size();
  if (n == 1) return 0; // 凸包退化成点或线段，则答案为0
  Point s;
  for (int i = 0; i < n; i++) s = s + A[i]; // 所有点x和y坐标之和
  A = ConvexHull(A), A.push_back(A[0]);
  double ans = 1e18;
  for (size_t i = 1; i < A.size(); i++) {
    const Point& a0 = A[i - 1], a = A[i]; // 作为备选直线
    Vector D = a - a0; // 点到直线的距离都是平行四边形面积➗D的长度
    ans = min(fabs((s.x - a0.x * n) * D.y - (s.y - a0.y * n) * D.x) / Length(D), ans);
  }
  return ans / n;
}

int main() {
  int T; cin >> T;
  for (int kase = 1, n; kase <= T; kase++) {
    cin >> n;
    vector<Point> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    printf("Case #%d: %.3lf\n", kase, solve(A));
  }
  return 0;
}
// 26040910 11168 Airport Accepted  C++ 0.030 2021-01-31 14:21:05