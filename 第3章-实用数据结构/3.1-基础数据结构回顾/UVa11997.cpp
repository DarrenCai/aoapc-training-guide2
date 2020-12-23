// 例题4  K个最小和（K Smallest Sums, UVa 11997）
// http://codeforces.com/gym/100048 C
// 陈锋
#include <bits/stdc++.h>
using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
typedef long long LL;
const int MAXK = 768, INF = 1e6 + 4;
int K, A[MAXK], B[MAXK];
struct Item {
  int sum, b;  // A[a] + B[b], b
  Item(int _sum, int _b) : sum(_sum), b(_b) {}
  bool operator<(const Item& i) const { return sum > i.sum; };
};

void merge() {  // AxB -> A
  priority_queue<Item> Q;
  _for(i, 0, K) Q.push(Item(A[i] + B[0], 0));
  _for(i, 0, K) {
    Item it = Q.top();
    Q.pop(), A[i] = it.sum;
    if (it.b < K - 1)
      Q.emplace(Item(it.sum + B[it.b + 1] - B[it.b], it.b + 1));
  }
}

void read_array(int *p) {
  _for(i, 0, K) scanf("%d", &(p[i]));
  sort(p, p + K);
}

int main() {
  while (scanf("%d", &K) == 1) {
    read_array(A);
    _for(i, 1, K) read_array(B), merge();
    _for(i, 0, K) printf("%d%c", A[i], i < K - 1 ? ' ' : '\n');
  }
  return 0;
}
// 18787064 11997 K Smallest Sums Accepted  C++11 0.110 2017-02-16 08:15:10