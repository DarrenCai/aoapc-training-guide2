// 例题33  等差数列（Arithmetic Progressions, CodeChef COUNTARI）
// 陈锋
#include <bits/stdc++.h>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
typedef long long LL;
const double EPS = 1e-10, PI = acos(-1);

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

const int N2 = 65536, MAXA = 30000, BLK_CNT = 30, MAXN = 100000 + 4;
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

void rec_rev_fft(valarray<Cplx>& A) { // DFT^(-1)，从y求a
  rec_fft_impl(A, 0, Arti_Epsilon);
  A *= 1.0 / A.size();
}
void rec_fft(valarray<Cplx>& A) { rec_fft_impl(A, 0, Epsilon); }
valarray<int> A(MAXN);
valarray<Cplx> A1(N2), A2(N2);
valarray<LL> PREV(0ll, N2), NEXT(0ll, N2), INSIDE(N2);
const double invN2 = 1.0 / N2;
int main() {
  int N; scanf("%d", &N);
  _for(i, 0, N) scanf("%d", &(A[i])), A[i]--, NEXT[A[i]]++;
  init_fft(N2); // 初始化所有的单位根
  LL ans = 0;
  int BLK_SZ = (N + BLK_CNT - 1) / BLK_CNT; /* 每个BLOCK的大小 */
  _for(bi, 0, BLK_CNT) {
    int L = bi * BLK_SZ, R = min((bi + 1) * BLK_SZ, N);
    _for(i, L, R) NEXT[A[i]]--;
    INSIDE = 0;
    _for(i, L, R) { /* 至少两个元素在这个Block内，且三个元素都不相等 */
      _for(j, i + 1, R) if (A[j] != A[i]) {
        int AK = 2 * A[i] - A[j];
        if (0 <= AK && AK < MAXA) ans += PREV[AK] + INSIDE[AK]; /* 考虑后两个元素是Ai和Aj */
        AK = 2 * A[j] - A[i]; /* 考虑前两个元素是Ai和Aj，则后一个元素必然在NEXT，
                    后一个元素在INSIDE的情况已经在上面考虑过了 */
        if (0 <= AK && AK < MAXA) ans += NEXT[AK];
      }
      INSIDE[A[i]]++;
    }

    _for(ak, 0, MAXA) { /* 三个元素相等=ak的情况 */
      LL ki = INSIDE[ak];
      ans += ki * (ki - 1) / 2 * (PREV[ak] + NEXT[ak]); // 两个元素在Block内 C(ki, 2) * (PREV + NEXT)
      ans += ki * (ki - 1) * (ki - 2) / 6; // 三个元素都在Block内 C(ki, 3)
    }

    if (bi > 0 && bi + 1 < BLK_CNT) { /* 只有中间元素在当前Block内 */
      _for(i, 0, N2) A1[i].init(PREV[i]), A2[i].init(NEXT[i]);
      rec_fft(A1), rec_fft(A2), A1 *= A2, rec_rev_fft(A1); // 卷积计算，计算分别位于Prev和Next内的两个和为2*ak的情况
      _for(ak, 0, MAXA) ans += INSIDE[ak] * llrint(A1[2 * ak].x);
    }

    _for(i, L, R) PREV[A[i]]++;
  }

  printf("%lld\n", ans);
  return 0;
}

// 11275383 2 min ago   sukhoeing       1.99    3.2M    C++14