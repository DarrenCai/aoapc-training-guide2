// 例题20  口吃的外星人（Stammering Aliens, SWERC 2009, LA4513）
// 陈锋
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
// #define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
typedef long long LL;
typedef unsigned long long ULL;
const int MAXN = 40000 + 8;
const ULL x = 123;
ULL H[MAXN], PX[MAXN], Hash[MAXN];
int N, sa[MAXN];
void init_PX() {
  PX[0] = 1;
  _for(i, 1, MAXN) PX[i] = x * PX[i - 1];
}

void init_hash(const string& s) {
  N = s.length();
  H[N] = 0;
  for (int i = N - 1; i >= 0; i--) H[i] = (s[i] - 'a' + 1) + H[i + 1] * x;
}

bool hash_cmp(int a, int b) {
  if (Hash[a] != Hash[b]) return Hash[a] < Hash[b];
  return a < b;
}

bool ok(int L, int M, int& pos) {  // 是否有长度至少len的substr出现M次以上
  _for(i, 0, N - L + 1) {
    sa[i] = i;
    Hash[i] = H[i] - H[i + L] * PX[L];
  }
  sort(sa, sa + N - L + 1, hash_cmp);
  pos = -1;
  int c = 0;
  _for(i, 0, N - L + 1) {
    if (i == 0 || Hash[sa[i]] != Hash[sa[i - 1]]) c = 0;
    if (++c >= M) pos = max(pos, sa[i]);
  }
  return pos >= 0;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  init_PX();
  string word;
  for (int t = 0, pos, M; cin >> M >> word && M; t++) {
    init_hash(word);
    if (!ok(1, M, pos)) {
      puts("none");
      continue;
    }
    int l = 1, r = N + 1;
    while (l + 1 < r) {
      int m = l + (r - l) / 2;
      if (ok(m, M, pos))
        l = m;
      else
        r = m;
    }
    ok(l, M, pos);
    printf("%d %d\n", l, pos);
  }
  return 0;
}
// Accepted 880ms 1613 C++ 5.3.0 2020-12-14 13:07:48 25845792