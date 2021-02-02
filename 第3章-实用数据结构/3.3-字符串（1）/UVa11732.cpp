// 例题14 strcmp()函数（“strcmp()” Anyone?, UVa11732）
// 詹益瑞,陈锋
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int SZ = 4e6 + 5, SIGMA = 70;
struct Trie {
  int ch[SZ][SIGMA], cnt[SZ], val[SZ], sz = 0;
  int idx(char c) {
    if (isdigit(c)) return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return c - 'a' + 38;
  }
  int newNode() {
    fill_n(ch[sz], SIGMA, 0), cnt[sz] = 0, val[sz] = 0;
    return sz++;
  }
  void insert(const char* s) {
    int len = strlen(s), u = 0;
    for (int i = 0; i < len; ++i) {
      int c = idx(s[i]), &uc = ch[u][c];
      if (!uc) uc = newNode();
      u = uc, cnt[u]++;
    }
    val[u]++; // 单词结束点
  }
  LL query(const char* s) {
    LL x = 0;
    int len = strlen(s), u = 0;
    for (int i = 0; i < len; ++i) {
      int c = idx(s[i]);
      if (!ch[u][c]) return x;
      // 不等的2个串的相同部分每个字符比较2次，最后一位不同的还有一次
      u = ch[u][c], x += cnt[u] * 2;
    }
    return x + val[u];
  }
  void init() { sz = 0, newNode(); }
};


Trie trie;
char s[1004];
int main() {
  for (int n, kase = 1; scanf("%d", &n) && n; kase++) {
    trie.init();
    LL ans = 0;
    for (int i = 1; i <= n; ++i)
      scanf("%s", s), ans += trie.query(s), trie.insert(s);
    ans += n * (n - 1) / 2; // 最后再补上每两个串的结尾比较一次
    printf("Case %d: %lld\n", kase, ans);
  }
  return 0;
}
// 26047697 11732 "strcmp()" Anyone?  Accepted  C++ 0.810 2021-02-02 06:31:12