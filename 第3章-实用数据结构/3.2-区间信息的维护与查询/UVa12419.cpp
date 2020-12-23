// 例题12  堆内存管理器（Heap Manager, UVa12419）
// 陈锋
#include <bits/stdc++.h>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
typedef long long LL;
const LL INF = 1ll << 60;
struct IntTreeNode {
  IntTreeNode *lc, *rc;
  int setv, lz, rz, mz; // 懒标记, [0~0***], [**0~0], [**0~0**]
  IntTreeNode() : lc(nullptr), rc(nullptr) { }
  inline void delchildren() {
    if (lc) delete lc;
    if (rc) delete rc;
    lc = rc = nullptr;
  }
  ~IntTreeNode() { delchildren(); } // C++析构函数，delete的时候会调用
  void mark(int l, int r, int v) {
    lz = rz = mz = (v == 0 ? r - l + 1 : 0);
    setv = v, delchildren();
  }

  void mark(IntTreeNode* &p, int l, int r, int v) {
    if (!p) p = new IntTreeNode();
    p->mark(l, r, v);
  }

  void pushdown(int l, int r) {  // 标记pushdown
    int m = l + (r - l) / 2;
    if (setv == -1) return;
    mark(lc, l, m, setv), mark(rc, m + 1, r, setv);
    setv = -1;
  }

  void set(int l, int r, int ql, int qr, int v) { // set [ql,qr] = v o->[l,r]
    if (ql <= l && r <= qr) {
      mark(l, r, v);
      return;
    }
    pushdown(l, r);
    int m = l + (r - l) / 2;
    IntTreeNode &ld = *(lc), &rd = *(rc);
    if (ql <= m) ld.set(l, m, ql, qr, v);
    if (qr > m) rd.set(m + 1, r, ql, qr, v);
    lz = (ld.lz == m - l + 1) ? ld.lz + rd.lz : ld.lz;
    rz = (rd.rz == r - m) ? rd.rz + ld.rz : rd.rz;
    mz = max(max(ld.mz, rd.mz), ld.rz + rd.lz);
  }
  int query(int l, int r, int len) { // 查询 o→[l,r]区间内最左边的>=len全0区间位置
    if (lz >= len) return l;  // [0~0***]
    pushdown(l, r);
    IntTreeNode &ld = *lc, &rd = *rc;
    int m = l + (r - l) / 2;
    if (ld.mz >= len) return ld.query(l, m, len);     // [**0~0**][**]
    if (ld.rz + rd.lz >= len) return m - ld.rz + 1;  // [**0~0][0~0**]
    return rd.query(m + 1, r, len);                    // [***][?]
  }
};
struct Event {  // release time, memory address [l,r]
  LL t;
  int l, r;
  bool operator<(const Event& a) const { return t > a.t; }
};
struct Process { int len, t, id; };  // slice len, use time, id
priority_queue<Event> EQ;
queue<Process> Q;
IntTreeNode A;
void allocate(int N, int b, LL cur, const Process& p) {  // 在cur时给p分配内存
  int l = A.query(0, N - 1, p.len);
  A.set(0, N - 1, l, l + p.len - 1, 1);
  EQ.push(Event{cur + p.t, l, l + p.len - 1});
  if (b) printf("%lld %d %d\n", cur, p.id, l);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int N, b, pcnt, m, p;
  for (LL t, ans = 0; cin >> N >> b;) {
    pcnt = 0, A.mark(0, N - 1, 0);
    for (int i = 1;; i++) {
      cin >> t >> m >> p; // time, mem slice len, time length
      if (t == 0 && m == 0 && p == 0) t = INF;
      while (!EQ.empty() && EQ.top().t <= t) {
        LL cur = EQ.top().t;  // 有释放内存的请求需要在t之前处理
        while (!EQ.empty() && EQ.top().t == cur) {  // 释放最近需要释放的内存
          const auto& e = EQ.top();
          ans = e.t;
          A.set(0, N - 1, e.l, e.r, 0), EQ.pop();
        }
        while (!Q.empty() && Q.front().len <= A.mz)
          allocate(N, b, cur, Q.front()), Q.pop();  // 需要分配内存的进程，分配内存
      }
      if (t == INF) break;
      if (A.mz >= m) allocate(N, b, t, Process{m, p, i}); // 现在就可以分配内存
      else Q.push(Process{m, p, i}), pcnt++;  // 排队
    }
    printf("%lld\n%d\n\n", ans, pcnt);  // 处理完所有进程，入过Q的进程
  }
  return 0;
}
// 24887303  12419   Heap Manager  Accepted  C++11   0.610   2020-04-17 02:50:01