// 「SCOI2005」王室联邦
// 陈锋
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

typedef long long LL;
const int NN = 1000 + 4;
vector<int> G[NN];
stack<int> S;
int N, B, BCnt, BId[NN], Cap[NN];  //块的个数，每个点所属块编号，每个块的中心

void dfs(int u, int fa) {
  size_t sz = S.size();
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs(v, u);
    if (S.size() >= sz + B) {  //新增点可以分块
      Cap[++BCnt] = u;         //新增块中心点为u
      while (S.size() > sz) BId[S.top()] = BCnt, S.pop();
    }
  }
  S.push(u);
  if (u == 1)  // root特殊处理，未分块的点都放入以root为中心的块
    while (!S.empty()) BId[S.top()] = BCnt, S.pop();
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> N >> B, BCnt = 0;
  for (int i = 1, u, v; i < N; i++) {
    cin >> u >> v;
    G[u].push_back(v), G[v].push_back(u);
  }
  dfs(1, -1);
  cout << BCnt << endl;
  for (int i = 1; i <= N; i++) cout << BId[i] << (i == N ? "\n" : " ");
  for (int i = 1; i <= BCnt; i++) cout << Cap[i] << (i == BCnt ? "\n" : " ");
  return 0;
}
// 46047872 「SCOI2005」王室联邦 答案正确 100 3 504 1000 C++ 2020-12-13 23:33:34