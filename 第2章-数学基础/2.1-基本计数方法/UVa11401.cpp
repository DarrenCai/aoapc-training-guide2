// 例题2  数三角形（Triangle Counting, UVa11401）
// Rujia Liu
#include <bits/stdc++.h>
using namespace std;

using LL = long long;  // int存不下
int main() {
  vector<LL> f(1e6 + 4);
  for (LL x = 4; x < (LL)f.size(); x++)
    f[x] = f[x - 1] + ((x - 1) * (x - 2) / 2 - (x - 1) / 2) / 2;  // 递推
  for (int n; cin >> n && n >= 3;) cout << f[n] << endl;
  return 0;
}
// 25877025 11401 Triangle Counting Accepted C++ 0.020 2020-12-23 01:22:22