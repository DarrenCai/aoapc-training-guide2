// 例题2  突击战（Commando War, UVa 11729）
// 陈锋
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

struct Job {
  int j, b;
  bool operator<(const Job& x) const {
    return j > x.j;  // 运算符重载。不要忘记const修饰符
  }
};

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  for (int n, b, j, kase = 1; cin >> n && n; kase++) {
    vector<Job> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].b >> v[i].j;
    sort(v.begin(), v.end());  //使用Job类的 < 运算符排序
    int ans = 0;
    for (int i = 0, s = 0; i < n; i++) {
      s += v[i].b;                 //当前任务的开始执行时间
      ans = max(ans, s + v[i].j);  //任务执行完毕时的最晚时间
    }
    printf("Case %d: %d\n", kase, ans);
  }
  return 0;
}
// 25875729	11729	Commando War	Accepted	C++	0.000	2020-12-22 14:21:50