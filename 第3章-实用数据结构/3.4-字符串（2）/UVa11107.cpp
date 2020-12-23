// 例题19  生命的形式（Life Forms, UVa 11107）
// 陈锋
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
typedef long long LL;

template <int SZ>
struct SuffixArray {
  int s[SZ];  // 原始字符数组（最后一个字符应必须是0，而前面的字符必须非0）
  int sa[SZ];      // 后缀数组
  int rank[SZ];    // 名次数组. rank[0]一定是n-1，即最后一个字符
  int height[SZ];  // height数组
  int t[SZ], t2[SZ], c[SZ];  // 辅助数组
  int n;                     // 字符个数

  void clear() { n = 0, fill_n(sa, SZ, 0); }

  // m为最大字符值加1。调用之前需设置好s和n
  void build_sa(int m) {
    int i, *x = t, *y = t2;
    for (i = 0; i < m; i++) c[i] = 0;
    for (i = 0; i < n; i++) c[x[i] = s[i]]++;
    for (i = 1; i < m; i++) c[i] += c[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1) {
      int p = 0;
      for (i = n - k; i < n; i++) y[p++] = i;
      for (i = 0; i < n; i++)
        if (sa[i] >= k) y[p++] = sa[i] - k;
      for (i = 0; i < m; i++) c[i] = 0;
      for (i = 0; i < n; i++) c[x[y[i]]]++;
      for (i = 0; i < m; i++) c[i] += c[i - 1];
      for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
      swap(x, y);
      p = 1;
      x[sa[0]] = 0;
      for (i = 1; i < n; i++)
        x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]
                       ? p - 1 : p++;
      if (p >= n) break;
      m = p;
    }
  }

  void build_height() {
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    for (int i = 0, k = 0; i < n; i++) {
      if (k) k--;
      int j = sa[rank[i] - 1];
      while (s[i + k] == s[j + k]) k++;
      height[rank[i]] = k;
    }
  }
};

const int MAXL = 1000 + 8, MAXN = 100 + 4;
int idx[MAXL * MAXN], flag[MAXN], N;
char buf[MAXL];
SuffixArray<MAXL * MAXN> sa;

bool good(int L, int R) {
  if (R - L <= N / 2) return false;
  fill_n(flag, MAXN, 0);
  int cnt = 0;
  _for(i, L, R) {
    int x = idx[sa.sa[i]];
    if (x != N && !flag[x]) flag[x] = 1, cnt++;
  }
  return cnt > N / 2;
}

void print_sub(int L, int R) {  // print s[L,R)
  _for(i, L, R) printf("%c", sa.s[i] - 1 + 'a');
  puts("");
}

bool print_sol(int len, bool print = false) {
  for (int L = 0, R = 1; R <= sa.n; R++) {
    if (R == sa.n || sa.height[R] < len) {  // 新开一段
      if (good(L, R)) {
        if (!print) return true;
        print_sub(sa.sa[L], sa.sa[L] + len);
      }
      L = R;
    }
  }
  return false;
}

void solve(int maxLen) {
  if (!print_sol(1)) {
    puts("?");
    return;
  }
  int L = 1, R = maxLen, M;
  while (L < R) {
    M = L + (R - L + 1) / 2;
    if (print_sol(M)) L = M;
    else R = M - 1;
  }
  print_sol(L, true);
}

// 给字符串加上一个字符，属于字符串i
void add(int ch, int i) { idx[sa.n] = i, sa.s[sa.n++] = ch; }

int main() {
  for (int t = 0; scanf("%d", &N) == 1 && N; t++) {
    if (t) puts("");
    int maxl = 0;
    sa.n = 0;
    _for(i, 0, N) {
      scanf("%s", buf);
      int sz = strlen(buf);
      maxl = max(maxl, sz);
      _for(j, 0, sz) add(buf[j] - 'a' + 1, i);
      add(100 + i, N);
    }
    add(0, N);
    if (N == 1)
      puts(buf);
    else
      sa.build_sa(N + 100), sa.build_height(), solve(maxl);
  }
  return 0;
}
// Accepted 70ms 3250 C++5.3.0 2020-12-1412:59:10 25845774