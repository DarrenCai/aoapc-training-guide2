// 例题10  宇航员分组（Astronauts, LA3713/UVa1391） CERC2006
// 陈锋
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 100000 + 5;

struct TwoSAT {
  int n;
  vector<int> G[maxn * 2];
  bool mark[maxn * 2];
  int S[maxn * 2], c;

  bool dfs(int x) {
    if (mark[x ^ 1]) return false;
    if (mark[x]) return true;
    mark[x] = true;
    S[c++] = x;
    for (int i = 0; i < G[x].size(); i++)
      if (!dfs(G[x][i])) return false;
    return true;
  }

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n * 2; i++) G[i].clear();
    memset(mark, 0, sizeof(mark));
  }

  // x = xval or y = yval
  void add_clause(int x, int xval, int y, int yval) {
    x = x * 2 + xval, y = y * 2 + yval;
    G[x ^ 1].push_back(y), G[y ^ 1].push_back(x);
  }

  bool solve() {
    for (int i = 0; i < n * 2; i += 2)
      if (!mark[i] && !mark[i + 1]) {
        c = 0;
        if (!dfs(i)) {
          while (c > 0) mark[S[--c]] = false;
          if (!dfs(i + 1)) return false;
        }
      }
    return true;
  }
};

#include <algorithm> //题目相关
int n, m, total_age, age[maxn];
int is_young(int x) { return age[x] * n < total_age; }
TwoSAT solver;
int main() {
  while (scanf("%d%d", &n, &m) == 2 && n) {
    total_age = 0;
    for (int i = 0; i < n; i++) scanf("%d", &age[i]), total_age += age[i];
    solver.init(n);
    for (int i = 0, a, b; i < m; i++) {
      scanf("%d%d", &a, &b), a--, b--;
      if (a == b) continue;
      solver.add_clause(a, 1, b, 1);    //不能同去任务C
      if (is_young(a) == is_young(b))   //同类宇航员
        solver.add_clause(a, 0, b, 0);  //不能同去任务A或者任务B
    }
    if (!solver.solve()) {
      puts("No solution.");
      continue;
    }
    for (int i = 0; i < n; i++)  // 看看x[i]的值
      if (solver.mark[i * 2])
        puts("C");  // false:去任务C
      else if (is_young(i))
        puts("B");  // true:年轻宇航员去任务B
      else
        puts("A");  // true: 年长宇航员去任务A
  }
  return 0;
}
// 5878107	1391	Astronauts	Accepted	C++	0.230	2020-12-23 08:07:31