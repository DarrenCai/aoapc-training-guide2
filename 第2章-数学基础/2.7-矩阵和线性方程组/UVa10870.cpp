// 例题26  递推关系（Recurrences, UVa 10870）
// 刘汝佳
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int NN = 20;
typedef long long Matrix[NN][NN];
typedef long long Vector[NN];

int sz, mod;
void matrix_mul(Matrix A, Matrix B, Matrix res) {
  Matrix C;
  memset(C, 0, sizeof(C));
  for (int i = 0; i < sz; i++)
    for (int j = 0; j < sz; j++)
      for (int k = 0; k < sz; k++)
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
  memcpy(res, C, sizeof(C));
}

void matrix_pow(Matrix A, int n, Matrix res) {
  Matrix a, r;
  memcpy(a, A, sizeof(a)), memset(r, 0, sizeof(r));
  for (int i = 0; i < sz; i++) r[i][i] = 1;
  while (n) {
    if (n & 1) matrix_mul(r, a, r);
    n >>= 1;
    matrix_mul(a, a, a);
  }
  memcpy(res, r, sizeof(r));
}

void transform(Vector d, Matrix A, Vector res) {
  Vector r;
  memset(r, 0, sizeof(r));
  for (int i = 0; i < sz; i++)
    for (int j = 0; j < sz; j++) r[j] = (r[j] + d[i] * A[i][j]) % mod;
  memcpy(res, r, sizeof(r));
}

int main() {
  for (int d, n, m; cin >> d >> n >> m && d;) {
    Matrix A;
    Vector a, f;
    for (int i = 0; i < d; i++) cin >> a[i], a[i] %= m;
    for (int i = d - 1; i >= 0; i--) cin >> f[i], f[i] %= m;
    memset(A, 0, sizeof(A));
    for (int i = 0; i < d; i++) A[i][0] = a[i];
    for (int i = 1; i < d; i++) A[i - 1][i] = 1;
    sz = d, mod = m;
    matrix_pow(A, n - d, A);
    transform(f, A, f);
    cout << f[0] << endl;
  }
  return 0;
}
// 25839977 10870 Recurrences Accepted C++ 0.030 2020-12-12 13:16:01