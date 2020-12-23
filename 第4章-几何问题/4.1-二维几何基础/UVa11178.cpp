// 例题1  Morley定理（Morley’s Theorem, UVa 11178）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
struct Point {
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;
Vector operator+(const Vector& A, const Vector& B) {
  return Vector(A.x + B.x, A.y + B.y);
}
Vector operator-(const Point& A, const Point& B) {
  return Vector(A.x - B.x, A.y - B.y);
}
Vector operator*(const Vector& A, double p) { return Vector(A.x * p, A.y * p); }
double Dot(const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector& A, const Vector& B) {
  return acos(Dot(A, B) / Length(A) / Length(B));
}
double Cross(const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }
Point GetLineIntersection(const Point& P, const Point& v, const Point& Q, const Point& w) {
  Vector u = P - Q;
  double t = Cross(w, u) / Cross(v, w);
  return P + v * t;
}
Vector Rotate(const Vector& A, double rad) {
  return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y; }
ostream& operator<<(ostream& os, const Point& p) { return os << p.x << " " << p.y; }
Point getD(Point A, Point B, Point C) {
  Vector v1 = C - B;
  double a1 = Angle(A - B, v1);
  v1 = Rotate(v1, a1 / 3);

  Vector v2 = B - C;
  double a2 = Angle(A - C, v2);
  v2 = Rotate(v2, -a2 / 3);

  return GetLineIntersection(B, v1, C, v2);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  cin >> T;
  for (Point A, B, C; T--;) {
    cin >> A >> B >> C;
    Point D = getD(A, B, C), E = getD(B, C, A), F = getD(C, A, B);
    printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n", 
      D.x, D.y, E.x, E.y, F.x, F.y);
  }
  return 0;
}
// 24480472 11178 Morley's Theorem  Accepted  C++11 0.020 2020-01-28 13:07:20