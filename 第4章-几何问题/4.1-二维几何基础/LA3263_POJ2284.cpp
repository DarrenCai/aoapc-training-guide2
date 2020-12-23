// 例题2  好看的一笔画（That Nice Euler Circuit, Shanghai 2004, LA3263）
// 陈锋
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
#define _for(i,a,b) for( int i=(a); i<(int)(b); ++i)

typedef long long LL;
const double eps = 1e-10;
int dcmp(double x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
int dcmp(double x, double y) { return dcmp(x - y); }

struct Point {
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  Point& operator=(const Point& p) {
    x = p.x, y = p.y;
    return *this;
  }
};
typedef Point Vector;

Vector operator+(const Vector& A, const Vector& B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator-(const Point& A, const Point& B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator*(const Vector& A, double p) { return Vector(A.x * p, A.y * p); }
bool operator==(const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
bool operator<(const Point& p1, const Point& p2) {
  if (p1.x != p2.x) return p1.x < p2.x;
  return p1.y < p2.y;
}
double Dot(const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector& A, const Vector& B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }
Vector Rotate(Vector A, double rad) { return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad)); }
Vector Normal(Vector A) {
  double L = Length(A);
  return Vector(-A.y / L, A.x / L);
}

bool SegmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
  double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1),
         c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
  return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
  Vector u = P - Q;
  double t = Cross(w, u) / Cross(v, w);
  return P + v * t;
}

bool OnSegment(const Point& p, const Point& a1, const Point& a2) {
  return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y; }
ostream& operator<<(ostream& os, const Point& p) { return os << p.x << " " << p.y; }

int main() {
  int N;
  for (int t = 1; cin >> N && N; t++) {
    Point p;
    set<Point> all_points;
    vector<Point> ps;
    _for(i, 0, N) cin >> p, ps.push_back(p), all_points.insert(p);
    int E = --N;
    _for(i, 0, N) _for(j, i + 1, N) 
      if (SegmentProperIntersection(ps[i], ps[i + 1], ps[j], ps[j + 1]))
        all_points.insert(GetLineIntersection(ps[i], ps[i + 1] - ps[i], ps[j], ps[j + 1] - ps[j]));

    for(set<Point>::iterator si = all_points.begin(); si != all_points.end(); si++)
      _for(i, 0, N) if (OnSegment(*si, ps[i], ps[i + 1])) E++;
    int F = E + 2 - all_points.size(); // V+F-E=2, 点，面，边
    printf("Case %d: There are %d pieces.\n", t, F);
  }
  return 0;
}
// Accepted 422ms 1300kB 3093 G++ 2020-12-14 14:16:59 22208849