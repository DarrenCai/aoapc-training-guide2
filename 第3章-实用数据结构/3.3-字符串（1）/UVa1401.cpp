// 例题13  背单词（Remember the Word, UVa1401）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
const int maxnode = 4000 * 100 + 10, sigma_size = 26;

// 字母表为全体小写字母的Trie
struct Trie {
  int ch[maxnode][sigma_size];
  int val[maxnode];
  int sz; // 结点总数
  void clear() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); } // 初始时只有一个根结点
  int idx(char c) { return c - 'a'; } // 字符c的编号

  // 插入字符串s，附加信息为v。注意v必须非0，因为0代表“本结点不是单词结点”
  void insert(const char *s, int v) {
    int u = 0, n = strlen(s);
    for (int i = 0; i < n; i++) {
      int c = idx(s[i]);
      if (!ch[u][c]) { // 结点不存在
        memset(ch[sz], 0, sizeof(ch[sz]));
        val[sz] = 0;  // 中间结点的附加信息为0
        ch[u][c] = sz++; // 新建结点
      }
      u = ch[u][c]; // 往下走
    }
    val[u] = v; // 字符串的最后一个字符的附加信息为v
  }

  // 找字符串s的长度不超过len的前缀
  void find_prefixes(const char *s, int len, vector<int>& ans) {
    int u = 0;
    for (int i = 0; i < len; i++) {
      if (s[i] == '\0') break;
      int c = idx(s[i]);
      if (!ch[u][c]) break;
      u = ch[u][c];
      if (val[u] != 0) ans.push_back(val[u]); // 找到一个前缀
    }
  }
};

// 文本串最大长度, 单词最大个数
const int TL = 3e5 + 4, WC = 4000 + 4, MOD = 20071027;
int D[TL], WLen[WC];
Trie trie;
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  string text, word;
  for (int kase = 1, S; cin >> text >> S; kase++) {
    trie.clear();
    for (int i = 1; i <= S; i++)
      cin >> word, WLen[i] = word.length(), trie.insert(word.c_str(), i);
    int L = text.length();
    fill_n(D, L, 0), D[L] = 1;
    for (int i = L - 1; i >= 0; i--) {
      vector<int> p;
      trie.find_prefixes(text.c_str() + i, L - i, p);
      for (size_t j = 0; j < p.size(); j++)
        D[i] = (D[i] + D[i + WLen[p[j]]]) % MOD;
    }
    printf("Case %d: %d\n", kase, D[0]);
  }
  return 0;
}
// Accepted 80ms 1784 C++ 5.3.0 2020-12-1411:33:14 25845627