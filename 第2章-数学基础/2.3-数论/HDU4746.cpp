// 例题14  墨菲斯（Mophues, ACM/ICPC Asia Regional Hangzhou Online 2013, HDU4746）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAXN = 500000 + 4, MAXP = MAXN;
vector<bool> isPrime(MAXP, true);
vector<LL> Mu(MAXP), Primes, H(MAXP, 1);
LL G[MAXN][20];
void sieve() {
  Mu[1] = 1, H[1] = 0;
  for (int i = 2; i < MAXP; ++i) {
    if (isPrime[i]) Primes.push_back(i), Mu[i] = -1, H[i] = 1;
    for(size_t j = 0; j < Primes.size(); ++j) {
      LL p = Primes[j], t = p * i;
      if (t >= MAXP) break;
      isPrime[t] = false, H[t] = H[i] + 1;
      if (i % p == 0) {
        Mu[t] = 0;
        break;
      }
      Mu[t] = -Mu[i];
    }
  }
  memset(G, 0, sizeof(G));
  for (int n = 1; n < MAXN; n++) {
    for (int k = 1, T = n; T < MAXN; ++k, T += n)
      G[T][H[n]] += Mu[k];  //Σμ(T/n)|h(n)=P
  }

  for (int n = 1; n < MAXN; n++) 
    for(int p = 1; p < 20; p++)
      G[n][p] += G[n][p - 1];  // Σμ(T/n)|h(n)≤P
  for (int n = 1; n < MAXN; n++) 
    for(int p = 0; p < 20; p++)  G[n][p] += G[n - 1][p];  // ∑nΣμ(T/n)|h(n)≤P
}

LL N, M, P;
LL solve() {
  if (P >= 20) return N * M;
  if (N > M) swap(N, M);
  LL ans = 0;
  for (int T = 1, et = 0; T <= N; T = et + 1) {
    et = min(N / (N / T), M / (M / T));  // All t in [T, et] same N/t, M/t
    ans += (G[et][P] - G[T - 1][P]) * (N / T) * (M / T);
  }
  return ans;
}

int main() {
  sieve();
  int Q;
  scanf("%d", &Q);
  while (Q--) {
    scanf("%lld%lld%lld", &N, &M, &P);
    printf("%lld\n", solve());
  }
  return 0;
}
// Accepted 608ms 88356kB 1456 G++ 2020-12-09 18:01:47 34811735