// 例题31  高尔夫机器人（Golf Bot, SWERC 2014, LA6886）
// 陈锋
#include <vector>
#include <iostream>
#include <cmath>
#include <complex>
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
using namespace std;
bool isPowOf2(int x) { return x && !(x & (x - 1)); }
typedef complex<double> Cplx;  // 复数 x + i*y
template<size_t N> // 多项式的阶
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

const double EPS = 1e-8;
const int MAXN = 1 << 18;  // 262144;
FFT<MAXN * 2> solver;
int main() {
  vector<int> A(MAXN);
  vector<Cplx> F(MAXN * 2);
  for (int n, M, x; scanf("%d", &n) == 1 && n;) {
    int N = 1;
    _for(i, 0, n) {
      scanf("%d", &(A[i]));
      while (A[i] * 2 > N) N *= 2;
    } // N是 >= max(A[i])的2的幂
    _for(i, 0, 2 * N) F[i] = Cplx();
    F[0].real(1);
    _for(i, 0, n) F[A[i]] = 1;
    solver.init_fft(N), solver.fft(F, N);
    for (int i = 0; i < N; i++) F[i] *= F[i];
    solver.idft(F, N);
    int ans = 0; scanf("%d", &M);
    _for(i, 0, M) {
      scanf("%d", &x);
      if (x < N && fabs(F[x].real()) > EPS) ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}
/*
算法分析请参考: 《入门经典训练指南-升级版》2.8节 例题31
*/
// Accepted 1010ms 46080kB 2618 C++14(gcc 8.3)2020-12-12 21:51:34 27085962