// 例题14  过路费（加强版）（The Toll! Revisited, UVa 10537）
// 陈锋
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;

const int NN = 52 + 10;
const long long INF = 1LL << 60;
typedef long long LL;

int N, G[NN][NN], St, Ed, P, Vis[NN]; // 标记
LL D[NN];     // D[i]表示从点i出发（已经交过点i的税了）时至少要带多少东西，到Ed时还能剩p个东西

int read_node() {
  char s[9];
  scanf("%s", s);
  if (isupper(s[0])) return s[0] - 'A';
  return s[0] - 'a' + 26;
}
char node_label(int u) { return u < 26 ? 'A' + u : 'a' + (u - 26); }
LL forward(LL k, int u) { // 拿着k个东西去结点u，还剩多少个东西
  if (u < 26) return k - (k + 19) / 20; // 镇子
  return k - 1; // 村子
}
// 至少要拿着多少个东西到达结点u，交税以后还能剩D[u]个东西
LL back(int u) {
  if (u >= 26) return D[u] + 1; // 村子
  LL X = D[u] * 20 / 19; // 初始值
  while (forward(X, u) < D[u]) X++; // 调整，容易理解的做法
  return X;
}
void solve() {
  N = 52; // 总是有52个结点
  fill_n(Vis, N + 1, 0), fill_n(D, N, INF);
  D[Ed] = P, Vis[Ed] = 1;
  for (int i = 0; i < N; i++)
    if (i != Ed && G[i][Ed]) D[i] = back(Ed);

  while (!Vis[St]) { // Dijkstra主过程，逆推，规模小就不要优先级队列了
    int minu = -1; // 找最小的D[u]的u
    for (int i = 0; i < N; i++)
      if (!Vis[i] && (minu < 0 || D[i] < D[minu])) minu = i;
    Vis[minu] = 1;
    for (int i = 0; i < N; i++)
      if (!Vis[i] && G[i][minu]) D[i] = min(D[i], back(minu)); // 更新其他结点的d
  }
  printf("%lld\n%c", D[St], node_label(St)); // 输出
  LL k = D[St]; // 当前手里有多少货?
  for (int u = St, next; u != Ed; u = next) {
    for (next = 0; next < N; next++) // 找到第一个可以走的结点
      if (G[u][next] && forward(k, next) >= D[next]) break;
    k = D[next];
    printf("-%c", node_label(next));
    u = next;
  }
  puts("");
}

int main() {
  for (int kase = 1; scanf("%d", &N) == 1 && N >= 0; kase++) {
    memset(G, 0, sizeof(G));
    for (int i = 0; i < N; i++) {
      int u = read_node(), v = read_node();
      if (u != v) G[u][v] = G[v][u] = 1;
    }
    scanf("%d", &P);
    St = read_node(), Ed = read_node();
    printf("Case %d:\n", kase);
    solve();
  }
  return 0;
}
// 25878179	10537	The Toll! Revisited	Accepted	C++	0.000	2020-12-23 08:23:15