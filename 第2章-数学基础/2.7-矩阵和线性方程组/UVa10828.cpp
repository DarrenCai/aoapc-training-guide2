// 例题28  随机程序（Back to Kernighan-Ritchie, UVa 10828）
// Rujia Liu
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const double eps = 1e-8;
const int NN = 100 + 10;
typedef double Matrix[NN][NN];

// 由于本题的特殊性，消元后不一定是对角阵，甚至不一定是阶梯阵
// 但若x[i]解惟一且有限，第i行除了A[i][i]和A[i][n]之外的其他元素均为0
void gauss_jordan(Matrix A, int n) {
  int i, j, k, r;
  for (i = 0; i < n; i++) {
    r = i;
    for (j = i + 1; j < n; j++)
      if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
    if (fabs(A[r][i]) < eps) continue;  // 放弃这一行，直接处理下一行 (*)
    if (r != i)
      for (j = 0; j <= n; j++) swap(A[r][j], A[i][j]);

    // 与除了第i行外的其他行进行消元
    for (k = 0; k < n; k++)
      if (k != i)
        for (j = n; j >= i; j--) A[k][j] -= A[k][i] / A[i][i] * A[i][j];
  }
}

int main() {
  int d[NN], inf[NN];
  Matrix A;
  vector<int> pre[NN];
  for (int kase = 1, n; scanf("%d", &n) == 1 && n; kase++) {
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n; i++) pre[i].clear();
    for (int a, b; scanf("%d%d", &a, &b) == 2 && a; pre[b].push_back(a))
      a--, b--, d[a]++;  // 改成从0开始编号, a的出度加1
    // 构造方程组
    memset(A, 0, sizeof(A));
    for (int i = 0; i < n; i++) {
      A[i][i] = 1;
      for (int j = 0; j < pre[i].size(); j++)
        A[i][pre[i][j]] -= 1.0 / d[pre[i][j]];
      if (i == 0) A[i][n] = 1;
    }

    // 解方程组，标记无穷变量
    gauss_jordan(A, n);
    memset(inf, 0, sizeof(inf));
    for (int i = n - 1; i >= 0; i--) {
      if (fabs(A[i][i]) < eps && fabs(A[i][n]) > eps)
        inf[i] = 1;  // 直接解出来的无穷变量
      for (int j = i + 1; j < n; j++)
        if (fabs(A[i][j]) > eps && inf[j])
          inf[i] = 1;  // 和无穷变量扯上关系的变量也是无穷的
    }

    int q, u;
    scanf("%d", &q);
    printf("Case #%d:\n", kase);
    while (q--) {
      scanf("%d", &u), u--;
      if (inf[u])
        printf("infinity\n");
      else
        printf("%.3lf\n", fabs(A[u][u]) < eps ? 0.0 : A[u][n] / A[u][u]);
    }
  }
  return 0;
}
// Accepted 20ms 2002 C++5.3.0 2020-12-12 21:41:59 25840104