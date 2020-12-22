// 例题32  瓷砖切割（Tile Cutting, World Finals 2007 LA7159）
// 陈锋
#include <bits/stdc++.h>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
typedef long long LL;
const double EPS = 1e-6, PI = acos(-1);

template<typename T>
struct Point { // x + y*i, complex number
  T x, y;
  Point& init(T _x = 0, T _y = 0) { x = _x, y = _y; return *this; }
  Point(T x = 0, T y = 0): x(x), y(y) {}
  Point& operator+=(const Point& p) { x += p.x, y += p.y; return *this; }
  Point& operator*=(const Point& p) { return init(x * p.x - y * p.y, x * p.y + y * p.x); }
};

template<typename T>
Point<T> operator+(const Point<T>& a, const Point<T>& b) { return {a.x + b.x, a.y + b.y};}
template<typename T>
Point<T> operator-(const Point<T>& a, const Point<T>& b) { return {a.x - b.x, a.y - b.y};}
template<typename T>
Point<T> operator*(const Point<T>& a, const Point<T>& b) { return {a.x*b.x - a.y * b.y, a.x*b.y + a.y * b.x}; }
typedef Point<double> Cplx; // complex number x + i*y

bool isPowOf2(int x) { return x && !(x & (x - 1)); }

const int MAXA = 1 << 19, N2 = 1 << 20; // 524288;
valarray<Cplx> Epsilon(N2), Arti_Epsilon(N2); // FFT和插值运算FFT所用的(w_n)^k
void rec_fft_impl(valarray<Cplx>& A, int level, const valarray<Cplx>& EP) {
  int n = A.size(), m = n / 2;
  if (n == 1) return;
  valarray<Cplx> A0(A[slice(0, m, 2)]), A1(A[slice(1, m, 2)]);
  rec_fft_impl(A0, level + 1, EP), rec_fft_impl(A1, level + 1, EP);
  _for(k, 0, m)
  A[k] = A0[k] + EP[k * (1 << level)] * A1[k], A[k + m] = A0[k] - EP[k * (1 << level)] * A1[k];
}
void init_fft(int n) { // 提前计算所有的(w_n)^k，大幅度提升递归fft的运行时间，免得每一层重复计算
  double theta = 2.0 * PI / n;
  _for(i, 0, n) {
    Epsilon[i].init(cos(theta * i), sin(theta * i)); // (w_n)^i
    Arti_Epsilon[i].init(Epsilon[i].x, -Epsilon[i].y);
  }
}
void idft(valarray<Cplx>& A) { // DFT^(-1)，从y求a
  rec_fft_impl(A, 0, Arti_Epsilon);
  A *= 1.0 / A.size();
}
void fft(valarray<Cplx>& A) { rec_fft_impl(A, 0, Epsilon); }

int main() {
  valarray<LL> C(0LL, N2); valarray<Cplx> F(N2);
  for (LL a = 1; a < MAXA; a++)
    for (LL b = 1; a * b < MAXA; b++) C[a * b]++;
  _for(i, 0, N2) F[i].init(C[i], 0);
  init_fft(N2);
  fft(F); F *= F; idft(F);
  int n; scanf("%d", &n);
  _for(i, 0, n) {
    LL maxW = -1; int al, ah, ans = 0;
    scanf("%d%d", &al, &ah);
    assert(al <= ah);
    _rep(a, al, ah) {
      LL w = llround(F[a].x);
      if (w > maxW) ans = a, maxW = w;
    }
    printf("%d %lld\n", ans, maxW);
  }

  return 0;
}
// 