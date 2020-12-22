// 例题29  乘积是平方数（Square, UVa 11542）
// Rujia Liu
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int NN = 500 + 10, maxp = 100;
int vis[NN], prime[maxp];
int gen_primes(int n) {
  int m = (int)sqrt(n + 0.5);
  fill_n(vis, NN, 0);
  for (int i = 2; i <= m; i++)
    if (!vis[i])
      for (int j = i * i; j <= n; j += i) vis[j] = 1;
  int c = 0;
  for (int i = 2; i <= n; i++)
    if (!vis[i]) prime[c++] = i;
  return c;
}

typedef int Matrix[NN][NN];

// m个方程，n个变量
int get_rank(Matrix A, int m, int n) {
  int i = 0, j = 0, k, r, u;
  while (i < m && j < n) {  // 当前正在处理第i个方程，第j个变量
    r = i;
    for (k = i; k < m; k++)
      if (A[k][j]) {
        r = k;
        break;
      }
    if (A[r][j]) {
      if (r != i)
        for (k = 0; k <= n; k++) swap(A[r][k], A[i][k]);
      // 消元后第i行的第一个非0列是第j列，且第u>i行的第j列均为0
      for (u = i + 1; u < m; u++)
        if (A[u][j])
          for (k = i; k <= n; k++) A[u][k] ^= A[i][k];
      i++;
    }
    j++;
  }
  return i;
}

Matrix A;

int main() {
  int m = gen_primes(500), T;
  cin >> T;
  while (T--) {
    int n, maxp = 0;
    long long x;  // 注意x的范围
    cin >> n;
    memset(A, 0, sizeof(A));
    for (int i = 0; i < n; i++) {
      cin >> x;
      for (int j = 0; j < m; j++)  // 求x中的prime[j]的幂，并更新系数矩阵
        while (x % prime[j] == 0)
          maxp = max(maxp, j), x /= prime[j], A[j][i] ^= 1;
    }
    int r = get_rank(A, maxp + 1, n);      // 只用到了前maxp+1个素数
    cout << (1LL << (n - r)) - 1 << endl;  // 空集不是解，所以要减1
  }
  return 0;
}
// Accepted 1573 C++ 5.3.0 2020-12-12 21:46:13 25840133