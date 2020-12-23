// 例题21  扩展成回文（Extend to Palindrome, UVa11475）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 4;
char S[MAXN], T[MAXN * 2];
int P[MAXN * 2];
void manacher(const char *s, int len) {
  int l = 0;
  T[l++] = '$', T[l++] = '#';
  for(int i = 0; i < len; i++) T[l++] = s[i], T[l++] = '#';
  T[l] = 0;
  int r = 0, c = 0;
  for(int i = 0; i < l; i++) {
    int &p = P[i];
    p = r > i ? min(P[2 * c - i], r - i) : 1;
    while(T[i + p] == T[i - p]) p++;
    if(i + p > r) r = i + p, c = i;
  }
}
int main() {
  while(scanf("%s", S) == 1) {
    int ans = 0, L = strlen(S);
    manacher(S, L);
    for(int i = 0; i < 2 * L + 2; i++)
      if(P[i] + i == 2 * L + 2) ans = max(ans, P[i] - 1); //此回文串是作为后缀出现的，更新答案
    printf("%s", S);
    for(int i = L - ans - 1; i >= 0; i--) printf("%c", S[i]);
    puts("");
  }
  return 0;
}
// 24183083 11475 Extend to Palindrome  Accepted  C++11 0.010 2019-11-12 07:25:40