// 例题3  阿格斯（Argus, Beijing 2004, POJ2051）
// 陈锋
#include<cstdio>
#include<queue>
using namespace std;

struct Item { // 优先队列中的元素
  int QNum, Period, Time;
  // 重要！优先级比较函数。优先级高的先出队
  bool operator < (const Item& a) const { // 这里的const必不可少，请读者注意
    if (Time != a.Time) return Time > a.Time;
    return QNum > a.QNum;
  }
};

int main() {
  priority_queue<Item> pq;
  char s[20];
  for (Item item; scanf("%s", s) && s[0] != '#'; pq.push(item)) {
    scanf("%d%d", &item.QNum, &item.Period);
    item.Time = item.Period; // 初始化“下一次事件的时间”为它的周期
  }
  int K;
  scanf("%d" , &K);
  while (K--) {
    Item r = pq.top(); // 取下一个事件
    pq.pop();
    printf("%d\n" , r.QNum);
    r.Time += r.Period; // 更新该触发器的“下一个事件”的时间
    pq.push(r); // 重新插入优先队列
  }
  return 0;
}
// Accepted 32ms 552kB 819 G++2020-12-1316:59:02 22207509