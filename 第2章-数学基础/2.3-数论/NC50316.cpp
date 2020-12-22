// 例题12  可怕的诗篇（A Horrible Poem，POI2012）
// 陈锋
#include <bits/stdc++.h>
using namespace std;

const int NN = 5e5 + 4, x = 263;
typedef unsigned long long ULL;
typedef long long LL;

ULL XP[NN];
void initXP() {
  XP[0] = 1;
  for (size_t i = 1; i < NN; i++) XP[i] = x * XP[i - 1];
}
template <size_t SZ>
struct StrHash {
  size_t N;
  ULL H[SZ];

  void init(const char* pc, size_t n = 0) {
    if (XP[0] != 1) initXP();
    if (n == 0) n = strlen(pc);
    N = n;
    assert(N > 0);
    assert(N + 1 < SZ);
    H[N] = 0;
    for (int i = N - 1; i >= 0; --i) H[i] = pc[i] - 'a' + 1 + x * (H[i + 1]);
  }

  void init(const string& S) { init(S.c_str(), S.size()); }
  inline ULL hash(size_t i, size_t j) {  // hash[i, j]
    // assert(i <= j);
    // assert(j < N);
    return H[i] - H[j + 1] * XP[j - i + 1];
  }
  inline ULL hash() { return H[0]; }
};

StrHash<NN> hs;
char S[NN];
int lastP[NN], primes[NN], pCnt;
void sieve(int N) {
  pCnt = 0;
  fill_n(lastP, N, 0);
  int* P = primes;
  for (int i = 2; i < N; ++i) {
    int& l = lastP[i];                 // i的最小素因子
    if (l == 0) l = i, P[pCnt++] = i;  // i是素数
    for (int j = 0; j < pCnt && P[j] <= l && P[j] * i < N; ++j)
      lastP[i * P[j]] = P[j];  // i*p的最小素因子是p
  }
}

int find_rep(int a, int b) {
  int L = b - a + 1, xl = L;
  while (xl > 1) {
    int p = lastP[xl];  // 尝试每一个素因子
    if (hs.hash(a, b - L / p) == hs.hash(a + L / p, b)) L /= p;
    xl /= p;
  }
  return L;
}

int main() {
  int n, q;
  S[0] = '|';
  scanf("%d%s%d", &n, S + 1, &q);
  hs.init(S, n + 1), sieve(n + 1);
  for (int i = 0, a, b; i < q; i++)
    scanf("%d%d", &a, &b), printf("%d\n", find_rep(a, b));
  return 0;
}
// 45995132	A Horrible Poem	答案正确 100 1117 24464 1612 C++ 2020-12-09