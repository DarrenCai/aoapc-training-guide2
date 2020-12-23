// 例题28  保守的老师（Guardian of Decency, NWERC 2005, LA 3415/POJ2771
// 陈锋
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500 + 5; // 单侧顶点的最大数目

// 二分图最大基数匹配，邻接矩阵写法
struct BPM {
  int n, m;               // 左右顶点个数
  int G[maxn][maxn];      // 邻接表
  int left[maxn];         // left[i]为右边第i个点的匹配点编号，-1表示不存在
  bool T[maxn];           // T[i]为右边第i个点是否已标记

  void init(int n, int m) {
    this->n = n, this->m = m;
    memset(G, 0, sizeof(G));
  }

  bool match(int u) {
    for (int v = 0; v < m; v++) if (G[u][v] && !T[v]) {
        T[v] = true;
        if (left[v] == -1 || match(left[v])) {
          left[v] = u;
          return true;
        }
      }
    return false;
  }

  // 求最大匹配
  int solve() {
    int ans = 0;
    fill_n(left, m + 1, -1);
    for (int u = 0; u < n; u++) { // 从左边结点u开始增广
      fill_n(T, m + 1, false);
      if (match(u)) ans++;
    }
    return ans;
  }
};

BPM solver;

#include<iostream>
#include<string>
struct Student {
  int h;
  string music, sport;
  Student(int h = 0, const string& music = "", const string& sport = "")
    : h(h), music(music), sport(sport) {}
};

bool conflict(const Student& a, const Student& b) {
  return abs(a.h - b.h) <= 40 && a.music == b.music && a.sport != b.sport;
}

int main() {
  int T; cin >> T;
  for (int t = 0, n; cin >> n, t < T; t++) {
    vector<Student> male, female;
    Student s;
    for (int i = 0; i < n; i++) {
      string gender;
      cin >> s.h >> gender >> s.music >> s.sport;
      if (gender[0] == 'M') male.push_back(s);
      else female.push_back(s);
    }
    int x = male.size(), y = female.size();
    solver.init(x, y);
    for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
        if (conflict(male[i], female[j])) solver.G[i][j] = 1;
    printf("%d\n", x + y - solver.solve());
  }
  return 0;
}
// Accepted 1641ms 1728kB 1908 G++ 2020-12-14 18:16:47 22209571