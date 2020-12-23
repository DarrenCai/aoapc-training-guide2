// 例题56  网格监控（Grid surveillance, IPSC 2011）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for( int i=(a); i<(int)(b); ++i)

template<int SZ>
struct BIT2D {
  struct Item {
    int ver, c;
    bool operator<(const Item& i) const {
      if (ver != i.ver) return ver < i.ver;
      return c < i.c;
    }
  };
  vector<Item> C[SZ][SZ];
  int vals[SZ][SZ], version;
  BIT2D() { version = 0; }
  int lowbit(int x) { return x & (x ^ (x - 1)); }
  void add(int x, int y, int c) {
    int ver = ++version;
    vals[x][y] += c;
    for (int i = x; i < SZ; i += lowbit(i))
      for (int j = y; j < SZ; j += lowbit(j)) {
        auto& v = C[i][j];
        v.push_back({ver, v.empty() ? c : v.back().c + c});
      }
  }
  // 版本ver中，[0,0] → [x,y] 区域的元素和
  int sum(int x, int y, int ver) {
    int ret = 0;
    for (int i = x; i > 0; i -= lowbit(i))
      for (int j = y; j > 0; j -= lowbit(j)) {
        auto &v = C[i][j];
        auto it = lower_bound(v.begin(), v.end(), (Item) {ver + 1, 0});
        if (it != v.begin()) ret += (--it)->c;
      }
    return ret;
  }
};

const int DIM = 4096;
int XM(int x, int C) { return (x ^ C) % 4096 + 3; }
BIT2D < DIM + 16 > S;

struct OP {
  int type, x1, x2, y1, y2, v;
  int exec(int c) {
    if (type == 1) {
      int x = XM(x1, c), y = XM(y1, c);
      S.add(x, y, v);
      return S.vals[x][y];
    }

    int _x1 = XM(x1, c), _x2 = XM(x2, c), _y1 = XM(y1, c) , _y2 = XM(y2, c);
    int xl = min(_x1, _x2), xr = max(_x1, _x2), yl = min(_y1, _y2), yr = max(_y1, _y2);
    int ver; // 版本号
    if (v == 0) ver = S.version;
    else if (v > 0) ver = v;
    else if (v < 0) ver = max(S.version + v, 0);
    return S.sum(xr, yr, ver) + S.sum(xl - 1, yl - 1, ver)
           - S.sum(xl - 1, yr, ver) - S.sum(xr, yl - 1, ver);
  }
};

istream& operator>>(istream& is, OP& o) {
  is >> o.type;
  if (o.type == 1) is >> o.x1 >> o.y1;
  if (o.type == 2) is >> o.x1 >> o.x2 >> o.y1 >> o.y2;
  return is >> o.v;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int r, q, qc = 0 ;
  cin >> r >> q;
  vector<OP> ops(q);
  for (auto& o : ops) {
    cin >> o;
    if (o.type == 2) qc++;
  }
  int c = 0, qi = 0;
  _for(i, 0, r) for (auto& o : ops) {
    c = o.exec(c);
    if (o.type == 2) {
      if (qi + 20000 >= r * qc) cout << c << endl;
      ++qi;
    }
  }
}
