// 例题17  Ardenia王国（Ardenia, CERC 2010, UVa1469）
// 陈锋
#include <bits/stdc++.h>
using namespace std;

struct Point3 {
  int x, y, z;
  Point3(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
};
istream& operator>>(istream& is, Point3& p) { return is >> p.x >> p.y >> p.z; }

typedef Point3 Vector3;

Vector3 operator+(const Vector3& A, const Vector3& B) {
  return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}
Vector3 operator-(const Point3& A, const Point3& B) {
  return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}
Vector3 operator*(const Vector3& A, int p) {
  return Vector3(A.x * p, A.y * p, A.z * p);
}
bool operator==(const Point3& a, const Point3& b) {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}
int Dot(const Vector3& A, const Vector3& B) {
  return A.x * B.x + A.y * B.y + A.z * B.z;
}
int Length2(const Vector3& A) { return Dot(A, A); }
Vector3 Cross(const Vector3& A, const Vector3& B) {
  return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z,
                 A.x * B.y - A.y * B.x);
}

typedef long long LL;
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }
LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }
struct Rat {
  LL a, b;
  Rat(LL a = 0) : a(a), b(1) {}
  Rat(LL x, LL y) : a(x), b(y) {
    if (b < 0) a = -a, b = -b;
    LL d = gcd(a, b);
    if (d < 0) d = -d;
    a /= d, b /= d;
  }
};

Rat operator+(const Rat& A, const Rat& B) {
  LL x = lcm(A.b, B.b);
  return Rat(A.a * (x / A.b) + B.a * (x / B.b), x);
}
Rat operator-(const Rat& A, const Rat& B) { return A + Rat(-B.a, B.b); }
Rat operator*(const Rat& A, const Rat& B) { return Rat(A.a * B.a, A.b * B.b); }
void updatemin(Rat& A, const Rat& B) {
  if (A.a * B.b > B.a * A.b) A.a = B.a, A.b = B.b;
}

// 点P到线段AB的距离的平方
Rat Rat_Dist2ToSeg(const Point3& P, const Point3& A, const Point3& B) {
  if (A == B) return Length2(P - A);
  Vector3 v1 = B - A, v2 = P - A, v3 = P - B;
  if (Dot(v1, v2) < 0) return Length2(v2);
  if (Dot(v1, v3) > 0) return Length2(v3);
  return Rat(Length2(Cross(v1, v2)), Length2(v1));
}

// 求异面直线p1+su和p2+tv的公垂线对应的s。如果平行/重合，返回false
bool Rat_LineDistance3D(const Point3& p1, const Vector3& u, const Point3& p2,
                        const Vector3& v, Rat& s) {
  LL b = (LL)Dot(u, u) * Dot(v, v) - (LL)Dot(u, v) * Dot(u, v);
  if (b == 0) return false;
  LL a = (LL)Dot(u, v) * Dot(v, p1 - p2) - (LL)Dot(v, v) * Dot(u, p1 - p2);
  s = Rat(a, b);
  return true;
}

void Rat_GetPointOnLine(const Point3& A, const Point3& B, const Rat& t, Rat& x,
                        Rat& y, Rat& z) {
  x = Rat(A.x) + Rat(B.x - A.x) * t;
  y = Rat(A.y) + Rat(B.y - A.y) * t;
  z = Rat(A.z) + Rat(B.z - A.z) * t;
}

Rat Rat_Distance2(const Rat& x1, const Rat& y1, const Rat& z1, const Rat& x2,
                  const Rat& y2, const Rat& z2) {
  return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  cin >> T;
  for (Point3 A, B, C, D; cin >> A >> B >> C >> D, T--;) {
    Rat s, t, ans = Rat(1e9);
    bool ok = false;
    if (Rat_LineDistance3D(A, B - A, C, D - C, s))
      if (s.a > 0 && s.a < s.b && Rat_LineDistance3D(C, D - C, A, B - A, t))
        if (t.a > 0 && t.a < t.b) {
          ok = true;  // 异面直线/相交直线
          Rat x1, y1, z1, x2, y2, z2;
          Rat_GetPointOnLine(A, B, s, x1, y1, z1),
              Rat_GetPointOnLine(C, D, t, x2, y2, z2);
          ans = Rat_Distance2(x1, y1, z1, x2, y2, z2);
        }
    if (!ok) {  // 平行直线/重合直线
      updatemin(ans, Rat_Dist2ToSeg(A, C, D)),
          updatemin(ans, Rat_Dist2ToSeg(B, C, D));
      updatemin(ans, Rat_Dist2ToSeg(C, A, B)),
          updatemin(ans, Rat_Dist2ToSeg(D, A, B));
    }
    cout << ans.a << " " << ans.b << endl;
  }
  return 0;
}
// Accepted 360ms 3795 C++ 5.3.0 2020-12-14 15:05:59 25846056