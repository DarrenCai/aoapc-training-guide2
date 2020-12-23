// 例题5  圆盘问题（Viva Confetti, Kanazawa 2002, UVa1308）
// 陈锋
#include <cmath>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const double eps = 5 * 1e-13;
int dcmp(double x) {
  if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}
const double PI = acos(-1), TWO_PI = PI * 2;

double NormalizeAngle(double rad, double center = PI) {
  return rad - TWO_PI * floor((rad + PI - center) / TWO_PI);
}
struct Point {
  double x, y;
  Point(double x = 0, double y = 0): x(x), y(y) { }
};

istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y; }

typedef Point Vector;
Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (const Point&A, const Point&B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x * p, A.y * p); }
Vector operator / (const Vector& A, double p) { return Vector(A.x / p, A.y / p); }
double Dot(const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double angle(const Vector& v) { return atan2(v.y, v.x); }

// 交点相对于圆1的极角保存在rad中
void getCircleCircleIntersection(const Point&c1, double r1, const Point&c2, double r2, vector<double>& rad) {
  double d = Length(c1 - c2);
  if (dcmp(d) == 0) return; // 不管是内含还是重合，都不相交
  if (dcmp(r1 + r2 - d) < 0) return;
  if (dcmp(fabs(r1 - r2) - d) > 0) return;
  double a = angle(c2 - c1), da = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
  rad.push_back(NormalizeAngle(a - da)), rad.push_back(NormalizeAngle(a + da));
}

const int maxn = 100 + 5;
int N;
Point center[maxn];
double radius[maxn];
bool vis[maxn];

// 覆盖点p的最上层的圆
int topmost(const Point& p) {
  for (int i = N - 1; i >= 0; i--)
    if (Length(center[i] - p) < radius[i]) return i;
  return -1;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  while (cin >> N && N) {
    for (int i = 0; i < N; i++)cin >> center[i] >> radius[i];
    fill_n(vis, N + 1, 0);
    for (int i = 0; i < N; i++) {
      vector<double> rad; // 考虑圆i被切割成的各个圆弧。把圆周当做区间来处理，起点是0，终点是2PI
      rad.push_back(0), rad.push_back(TWO_PI);
      for (int j = 0; j < N; j++)
        getCircleCircleIntersection(center[i], radius[i], center[j], radius[j], rad);
      sort(rad.begin(), rad.end());

      for (size_t j = 0; j < rad.size(); j++) {
        double mid = (rad[j] + rad[j + 1]) / 2.0; // 圆弧中点相对于圆i圆心的极角
        for (int side = -1; side <= 1; side += 2) {
          double r2 = radius[i] - side * eps; // 往里面或者外面稍微一动一点点
          int t = topmost(Point(center[i].x + cos(mid) * r2, center[i].y + sin(mid) * r2));
          if (t >= 0) vis[t] = true;
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) if (vis[i]) ans++;
    cout << ans << "\n";
  }
  return 0;
}
// 25877748	1308	Viva Confetti	Accepted	C++	0.000	2020-12-23 06:39:24