// 例题4  多叉树遍历（Exploring Pyramids, NEERC 2005, Codeforces Gym101334E）
// Rujia Liu
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 300 + 10;
const int MOD = 1000000000;
typedef long long LL;

char S[maxn];
int d[maxn][maxn];

int dp(int i, int j) {
  if(i == j) return 1;
  if(S[i] != S[j]) return 0;
  int& ans = d[i][j];
  if(ans >= 0) return ans;
  ans = 0;
  for(int k = i+2; k <= j; k++) if(S[i] == S[k])
    ans = (ans + (LL)dp(i+1,k-1) * (LL)dp(k,j)) % MOD;
  return ans;
}

int main() {
  freopen("exploring.in", "r", stdin);
  freopen("exploring.out", "w", stdout);
  while(scanf("%s", S) == 1) {
    memset(d, -1, sizeof(d));
    printf("%d\n", dp(0, strlen(S)-1));
  }
  return 0;
}
// 102083028 	Dec/23/2020 09:32UTC+8 	chenwz 	E - Exploring Pyramids 	GNU C++11 	Accepted 	61 ms 	300 KB 