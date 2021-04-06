// 例题32  瓷砖切割（Tile Cutting, World Finals 2007 LA7159）
// 陈锋
#include <bits/stdc++.h>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
typedef long long LL;

typedef complex<double> Cplx;  // 复数 x + i*y
template<size_t N> // 多项式次数*2
struct FFT {
  const double PI = acos(-1);
  Cplx Epsilon[N], Arti_Epsilon[N]; // FFT和插值运算FFT所用的(w_n)^k
  void slice_vec(const vector<Cplx>& v, int start, int step, vector<Cplx> &ans) {
    ans.clear();
    for (size_t i = start; i < v.size(); i += step) ans.push_back(v[i]);
  }
  void rec_fft_impl(vector<Cplx>& A, int n, int level, const Cplx* EP) {
    int m = n / 2;
    if (n == 1) return;
    vector<Cplx> A0, A1;
    slice_vec(A, 0, 2, A0), slice_vec(A, 1, 2, A1);
    rec_fft_impl(A0, m, level + 1, EP), rec_fft_impl(A1, m, level + 1, EP);
    _for(k, 0, m) {
      A[k] = A0[k] + EP[k * (1 << level)] * A1[k];
      A[k + m] = A0[k] - EP[k * (1 << level)] * A1[k];
    }
  }
  // 提前计算所有的(w_n)^k，提升递归fft的运行时间，免得每一层重复计算
  void init_fft(int n) {
    double theta = 2.0 * PI / n;
    _for(i, 0, n) {
      Epsilon[i] = Cplx(cos(theta * i), sin(theta * i));  // (w_n)^i
      Arti_Epsilon[i] =  conj(Epsilon[i]); // 共轭复数
    }
  }
  void idft(vector<Cplx>& A, int n) {  // DFT^(-1)，从y求a
    rec_fft_impl(A, n, 0, Arti_Epsilon);
    for (size_t i = 0; i < A.size(); i++) A[i] /= n;
  }
  void fft(vector<Cplx>& A, int n) { rec_fft_impl(A, n, 0, Epsilon); }
};

const double EPS = 1e-6;
const int MAXA = 1 << 19, N2 = 1 << 20; // 524288;
FFT<N2> solver;

int main() {
  vector<LL> C(N2, 0LL);
  vector<Cplx> F(N2);
  for (LL a = 1; a < MAXA; a++)
    for (LL b = 1; a * b < MAXA; b++) C[a * b]++;
  _for(i, 0, N2) F[i] = Cplx(C[i], 0);
  solver.init_fft(N2), solver.fft(F, N2);
  for (int i = 0; i < N2; i++) F[i] *= F[i];
  solver.idft(F, N2);
  int n; scanf("%d", &n);
  _for(i, 0, n) {
    LL maxW = -1; int al, ah, ans = 0;
    scanf("%d%d", &al, &ah); assert(al <= ah);
    for (int a = al; a <= ah; a++) {
      LL w = llround(F[a].real());
      if (w > maxW) ans = a, maxW = w;
    }
    printf("%d %lld\n", ans, maxW);
  }
  return 0;
}
// Accepted 780ms  2504  C++  2021-04-0416:10:15            7107540