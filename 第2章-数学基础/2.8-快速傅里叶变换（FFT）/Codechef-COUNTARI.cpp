// 例题33  等差数列（Arithmetic Progressions, CodeChef COUNTARI）
// 陈锋
#include <vector>
#include <iostream>
#include <cmath>
#include <complex>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
typedef long long LL;
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
  void dft(vector<Cplx>& A, int n) { rec_fft_impl(A, n, 0, Epsilon); }
};
const int N2 = 65536, MAXA = 30000, BLK_CNT = 30, MAXN = 1e5 + 4;
FFT<N2> solver;
vector<int> A(MAXN);
vector<Cplx> A1(N2), A2(N2);
vector<LL> PREV(N2, 0ll), NEXT(N2, 0ll), INSIDE(N2);
int main() {
  int N; scanf("%d", &N);
  _for(i, 0, N) scanf("%d", &(A[i])), A[i]--, NEXT[A[i]]++;
  solver.init_fft(N2); // 初始化所有的单位根
  LL ans = 0;
  int BLK_SZ = (N + BLK_CNT - 1) / BLK_CNT; /* 每个BLOCK的大小 */
  _for(bi, 0, BLK_CNT) {
    int L = bi * BLK_SZ, R = min((bi + 1) * BLK_SZ, N);
    _for(i, L, R) NEXT[A[i]]--;
    fill(INSIDE.begin(), INSIDE.end(), 0);
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
      _for(i, 0, N2) A1[i] = Cplx(PREV[i], 0), A2[i] = Cplx(NEXT[i], 0);
      solver.dft(A1, N2), solver.dft(A2, N2);
      for (size_t i = 0; i < A1.size(); i++) A1[i] *= A2[i];
      solver.idft(A1, N2); // 卷积计算，计算分别位于Prev和Next内的两个和为2*ak的情况
      _for(ak, 0, MAXA) ans += INSIDE[ak] * llrint(A1[2 * ak].real());
    }

    _for(i, L, R) PREV[A[i]]++;
  }
  printf("%lld\n", ans);
  return 0;
}
// 11275383 2 min ago   sukhoeing       1.99    3.2M    C++14