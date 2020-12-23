// 例题46  公交路线（Bus Routes, ACM/ICPC Asia-Hefei 2015, HDU5552）
// 陈锋
#include <bits/stdc++.h>
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
using namespace std;
typedef long long LL;
const int MOD = 152076289, NN = 10000 + 8;
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }
void exgcd(LL a, LL b, LL &x, LL &y) {
  if (!b) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x), y -= a / b * x;
}
inline LL mul_mod(LL a, LL b) { return a * b % MOD; }
inline LL pow_mod(LL a, LL p) {
  LL res = 1;
  for (; p > 0; p >>= 1, (a *= a) %= MOD)
    if (p & 1) (res *= a) %= MOD;
  return res;
}
inline LL inv(LL a) {
  LL x, y;
  exgcd(a, MOD, x, y);
  return (x % MOD + MOD) % MOD;
}

namespace _Polynomial {
const int g = 106;  // 原根
int A[NN << 1], B[NN << 1];
int w[NN << 1], r[NN << 1];
void DFT(int *a, int op, int n) {
  _for(i, 0, n) if (i < r[i]) swap(a[i], a[r[i]]);
  for (int i = 2; i <= n; i <<= 1)
    for (int j = 0; j < n; j += i)
      for (int k = 0; k < i / 2; k++) {
        int u = a[j + k],
            t = (LL)w[op == 1 ? n / i * k : (n - n / i * k) & (n - 1)] *
                a[j + k + i / 2] % MOD;
        a[j + k] = (u + t) % MOD, a[j + k + i / 2] = (u - t) % MOD;
      }
  if (op == -1) {
    int I = inv(n);
    _for(i, 0, n) a[i] = (LL)a[i] * I % MOD;
  }
}
void multiply(const int *a, const int *b, int *c, int n1, int n2) {
  int n = 1;
  while (n < n1 + n2 - 1) n <<= 1;
  copy_n(a, n1, A), copy_n(b, n2, B);
  fill(A + n1, A + n, 0), fill(B + n2, B + n, 0);

  _for(i, 0, n) r[i] = (r[i >> 1] >> 1) | ((i & 1) * (n >> 1));
  w[0] = 1, w[1] = pow_mod(g, (MOD - 1) / n);
  _for(i, 2, n) w[i] = mul_mod(w[i - 1], w[1]);

  DFT(A, 1, n), DFT(B, 1, n);
  _for(i, 0, n) A[i] = mul_mod(A[i], B[i]);
  DFT(A, -1, n);
  _for(i, 0, n1 + n2 - 1) c[i] = (A[i] + MOD) % MOD;
}
};  // namespace _Polynomial

int A[NN], B[NN], C[NN * 2];
LL Fact[NN], FactInv[NN], F[NN], G[NN];
void solve(int l, int r) {
  if (l == r) {
    F[l] = (G[l] - mul_mod(Fact[l - 1], F[l])) % MOD;
    return;
  }
  int m = (l + r) / 2;
  solve(l, m);  // F[l~m] -> F(m,r]
  _rep(i, l, m) A[i - l] =
      mul_mod(F[i], FactInv[i - 1]);  // ∑F(i)/(i-1)!, i = l~m

  for (int i = r - 1, j = 0; i >= l; --i, ++j)
    B[j] = mul_mod(G[r - i], FactInv[r - i]);
  _Polynomial::multiply(A, B, C, m - l + 1, r - l);
  _rep(i, m + 1, r)(F[i] += C[i - l - 1]) %= MOD;
  solve(m + 1, r);
}

int main() {
  Fact[0] = Fact[1] = 1, FactInv[0] = FactInv[1] = 1;  // i!, (i!)^-1 % MOD
  _for(i, 2, NN) Fact[i] = mul_mod(Fact[i - 1], i), FactInv[i] = inv(Fact[i]);
  LL m;
  int T;
  scanf("%d", &T);
  for (int t = 1, n; t <= T; t++) {
    scanf("%d%lld", &n, &m);
    fill_n(F, n + 1, 0);
    _rep(i, 1, n) G[i] = pow_mod(m + 1, (LL)i * (i - 1) / 2);
    solve(1, n);
    printf("Case #%d: %lld\n", t,
           ((F[n] - pow_mod(n, n - 2) * pow_mod(m, n - 1)) % MOD + MOD) % MOD);
  }
  return 0;
}
// 34867205 2020-12-13 23:04:33 Accepted 5552 1076MS 2072K 2947 B G++ chenwz