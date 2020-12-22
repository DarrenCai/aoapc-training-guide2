// 例题6  葛伦堡博物馆（Glenbow Museum, World Finals 2008, UVa1073）
// Rujia Liu
#include<cstdio>
#include<cstring>
const int maxn = 1000;

long long d[maxn+1][5][2], ans[maxn+1];

int main() {
  memset(d, 0, sizeof(d));
  for(int k = 0; k < 2; k++) {
    d[1][0][k] = 1;
    for(int i = 2; i <= maxn; i++)
      for(int j = 0; j < 5; j++) {
        d[i][j][k] = d[i-1][j][k];
        if(j > 0) d[i][j][k] += d[i-1][j-1][k];
      }
  }

  memset(ans, 0, sizeof(ans));
  for(int i = 1; i <= maxn; i++) {
    if(i < 4 || i % 2 == 1) continue;
    int R = (i+4)/2;    
    ans[i] = d[R][3][0] + d[R][4][1] + d[R][4][0];
  }

  int n, kase = 1;
  while(scanf("%d", &n) == 1 && n)
    printf("Case %d: %lld\n", kase++, ans[n]);
  return 0;
}
// 25877043  1073  Glenbow Museum  Accepted  C++  0.000  2020-12-23 01:32:37