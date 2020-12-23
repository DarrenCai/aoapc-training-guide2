// 例题11  山脉（Mountains, IOI05, SPOJ NKMOU）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Node {
  LL sum, maxp; // 区间和，最大非负前缀
  Node *left, *right;
  int val;
  inline bool isleaf() { return !left && !right; }
  inline void init() { memset(this, 0, sizeof(Node));}
  inline void delchildren() {
    if (left) delete left;
    if (right) delete right;
    left = right = nullptr;
  }
  ~Node() { delchildren(); } // C++析构函数，delete的时候会调用
};
typedef Node* PN;
int N;
PN root;
void maintain(Node& p) {
  p.sum = p.left->sum + p.right->sum;
  p.maxp = max(p.left->maxp, p.left->sum + p.right->maxp);
}
void setval(Node& p, int v, int L, int R) {
  assert(L <= R); // 整个区间设置值
  p.sum = (LL)(p.val = v) * (R - L + 1);
  p.maxp = max(0LL, p.sum);
  p.delchildren(); // 左右孩子都可以不要了
}
void pushdown(Node& p, int L, int R) {
  int M = (L + R) / 2;
  p.left = new Node(), p.right = new Node();
  setval(*(p.left), p.val, L, M), setval(*(p.right), p.val, M + 1, R);
}
void modify(int l, int r, int v, Node& p = *root, int nL = 1, int nR = N) {
  int M = (nL + nR) / 2;
  if (l <= nL && nR <= r) {
    setval(p, v, nL, nR);
    return;
  }
  if (p.isleaf()) pushdown(p, nL, nR); // 左右区间创建子节点
  if (l <= M) modify(l, r, v, *(p.left), nL, M); // 递归
  if (r > M) modify(l, r, v, *(p.right), M + 1, nR); // 递归
  maintain(p); // 维护sum以及maxp
}
// 查询数组中前缀和<=h的最长前缀的右端点位置
int query(LL h, Node& p = *root, int L = 1, int R = N) {
  if (h >= p.maxp) return R; // 整个区间都行
  if (p.isleaf()) return L + (h / p.val) - 1; // 区间元素都相等，按比例返回
  int M = (L + R) / 2;
  Node& pl = *(p.left);
  return h >= pl.maxp ? query(h - pl.sum, *(p.right), M + 1, R) // 左边的最大非负前缀<=h，一定能跑到右边
         : query(h, pl, L, M); // 只能在左子区间内部
}

void dbgprint(Node& p = *root, int L = 1, int R = N) { // 打印数组，调试用
  if (p.isleaf()) {
    for (int i = L; i <= R; i++) printf("%d ", p.val);
    return;
  }
  int M = (L + R) / 2;
  dbgprint(*(p.left), L, M), dbgprint(*(p.right), M + 1, R);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> N;
  string s;
  root = new Node();
  for (int a, b, d, h; cin >> s && s[0] != 'E'; ) {
    if (s[0] == 'I') cin >> a >> b >> d, modify(a, b, d);
    else cin >> h, cout << query(h) << endl;
  }
  delete root;
  return 0;
}
// 25407608 2020-02-16 07:12:57 Feng Chen IOI05 Mountains 100 2.62 169M CPP14