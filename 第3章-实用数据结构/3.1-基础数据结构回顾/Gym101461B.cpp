// 例题6  合作网络（Corporative Network, Codeforces Gym 101461B）
// Rujia Liu
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
const int maxn = 20000 + 10;
int pa[maxn], d[maxn];
int findset(int x) {
  if (pa[x] == x) return x;
  int root = findset(pa[x]);
  d[x] += d[pa[x]];
  return pa[x] = root;
}

int main() {
  freopen("network.in", "r", stdin);
  freopen("network.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int kase = 0, n, u, v; kase < T; kase++) {
    string cmd;
    cin >> n;
    for (int i = 1; i <= n; i++) pa[i] = i, d[i] = 0;
    while (cin >> cmd && cmd[0] != 'O') {
      if (cmd[0] == 'E') cin >> u, findset(u), cout << d[u] << endl;
      if (cmd[0] == 'I') cin >> u >> v, pa[u] = v, d[u] = abs(u - v) % 1000;
    }
  }
  return 0;
}
// 102162738 Dec/24/2020 11:38UTC+8 B - Corporative Network GNU C++11 Accepted 343 ms 300 KB