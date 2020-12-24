// 例题5  蚂蚁（Piotr’s Ants, UVa 10881）
// Rujia Liu
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 10000 + 5;

struct Ant {
  int id;  // 输入顺序
  int p;   // 位置
  int d;   // 朝向。 -1: 左; 0:转身中; 1:右
  bool operator<(const Ant& a) const { return p < a.p; }
} before[maxn], after[maxn];
const char dirName[][10] = {"L", "Turning", "R"};
int order[maxn];  //输入的第i只蚂蚁是终态中的左数第order[i]只蚂蚁
int main() {
  int K; scanf("%d", &K);
  for (int kase = 1, L, T, n; kase <= K; kase++) {
    scanf("%d%d%d", &L, &T, &n);
    for (int i = 0, p, d; i < n; i++) {
      char c;
      scanf("%d %c", &p, &c);
      d = (c == 'L' ? -1 : 1);
      // 相撞后可以看做对穿而过,这里id是未知的
      before[i] = (Ant){i, p, d}, after[i] = (Ant){0, p + T * d, d};
    }
    printf("Case #%d:\n", kase);
    sort(before, before + n);  //计算order数组
    for (int i = 0; i < n; i++)
      order[before[i].id] = i;  // 第一次从左到右所有的蚂蚁的相对位置没有变化
    sort(after, after + n);          //计算终态
    for (int i = 0; i < n - 1; i++)  //修改碰撞中的蚂蚁的方向
      if (after[i].p == after[i + 1].p) after[i].d = after[i + 1].d = 0;
    for (int i = 0; i < n; i++) {
      int a = order[i];
      if (after[a].p < 0 || after[a].p > L)
        puts("Fell off");
      else
        printf("%d %s\n", after[a].p, dirName[after[a].d + 1]);
    }
    printf("\n");
  }
  return 0;
}
// 25879739 10881 Piotr's Ants Accepted C++ 0.010 2020-12-23 15:21:04