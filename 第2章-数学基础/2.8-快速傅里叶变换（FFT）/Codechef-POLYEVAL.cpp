// 例题34  多项式求值（Evaluate the polynomial, CodeChef POLYEVAL）
// 陈锋
#include <bits/stdc++.h>
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;
typedef long long LL;
const int MOD = 786433, K = 1 << 18, w = 1000;
typedef vector<int> IVec;
int add_mod(int a, int b) {
  LL ret = a + b;
  while (ret < 0) ret += MOD;
  return ret % MOD;
}
int mul_mod(int a, int b) { return (((LL)a) * b) % MOD; }
int pow_mod(int a, int b) {
  LL ans = 1;
  while (b > 0) {
    if (b & 1) ans = mul_mod(ans, a);
    a = mul_mod(a, a);
    b /= 2;
  }
  return ans;
}
int getGen(int P) {  // 原根
  unordered_set<int> set;
  _for(g, 1, P) {
    set.clear();
    int pm = g;
    _for(ex, 1, P) {
      if (set.count(pm)) break;
      set.insert(pm);
      pm = (pm * g) % P;
    }
    if (set.size() == MOD - 1) {  // 找到原根了
      assert(pm == g);
      return g;
    }
  }
  return -1;
}
int eval(const IVec& A, int x) {  // 求A(x)
  int ans = 0, cur = 1;
  for (size_t i = 0; i < A.size(); i++)
    ans = add_mod(ans, mul_mod(A[i], cur)), cur = mul_mod(cur, x);
  return ans;
}
IVec slice_vec(const IVec& vec, int start, int step) {
  IVec ans;
  for (size_t i = start; i < vec.size(); i += step) ans.push_back(vec[i]);
  return ans;
}
// 对于多项式A(x), 使用{w^0, w^1, w^(K-1)}做DFT(数论模运算)
IVec NTT(const IVec& A, const IVec& W, int level = 1) {
  int n = W.size() / level, m = n / 2, An = A.size();
  IVec ans(n, 0);
  if (An < 1) return ans;
  if (n <= 2) {
    _for(i, 0, n) ans[i] = eval(A, W[level * i]);
    return ans;
  }
  const IVec &A0 = NTT(slice_vec(A, 0, 2), W, level * 2),
              &A1 = NTT(slice_vec(A, 1, 2), W, level * 2);
  _for(i, 0, n) ans[i] = add_mod(A0[i % m], mul_mod(W[level * i], A1[i % m]));
  return ans;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  const int g = getGen(MOD);
  int n;
  cin >> n;
  n++;
  IVec A(n), ans(MOD), W(K), B(n);
  _for(i, 0, n) cin >> A[i];
  _for(i, 0, K) W[i] = pow_mod(w, i);
  _rep(c, 0, 2) {
    _for(i, 0, n) B[i] = mul_mod(A[i], pow_mod(g, c * i));
    const IVec& Y = NTT(B, W);
    _for(i, 0, K) ans[mul_mod(pow_mod(g, c), W[i])] = Y[i];
  }
  ans[0] = A[0];
  int Q, x;
  cin >> Q;
  while (Q--) cin >> x, cout << ans[x] << endl;
  return 0;
}
// Accepted 1520ms 25292kB 2222 C++14(gcc 6.3)2020-12-12 21:56:24 40368549