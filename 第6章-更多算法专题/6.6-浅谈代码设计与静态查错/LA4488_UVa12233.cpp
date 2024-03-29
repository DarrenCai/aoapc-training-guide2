// LA4488/UVa12233 Final Combat：正确版
// Rujia Liu
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>
using namespace std;

const int MAXTIME = 12;
const int INF = 100000000;
const string name[] = {"Y", "H", "L", "M"};

int SY_jing, XX_su, SY_su, yurun_jing, yurun_shen, shuerguo_shen;
int maxjing[4], maxshen[4], su[4];
int d1x[4], d2x[4], d1s[4], d2s[4];
int wad[4], ssd[4], ssq[4], ssp[4], q1[4], q2[4];
int jing[4], qi[4], shen[4];

int MaxT, Hero, Pos, HeroT, XXT, SYT;
map<int,int> Hash[MAXTIME + 1];
int dfs(int t, int j, int q, int s) {
  if(j <= 0) return -INF;
  if(t > MaxT) return 0;
  j = min(j, maxjing[Hero]); q = min(q, 100); s = min(s, maxshen[Hero]);
  int h = j*110000 + q*1000 + s;
  if(Hash[t].count(h)) return Hash[t][h];
  int dj = 0, dq = 0;
  if(t % XXT == 0) {
    if((t / XXT) % 4 == Pos) { dj -= d1x[Hero]; dq += q2[Hero]; }
    if((t / XXT) % 4 == 0) dj -= d2x[Hero];
  }
  if(t % SYT == 0) {
    if((t / SYT) % 4 == Pos) { dj -= d1s[Hero]; dq += q2[Hero]; }
    if((t / SYT) % 4 == 0) dj -= d2s[Hero];
  }
  Hash[t][h] = -INF;
  int& ans = Hash[t][h];
  if(t == MaxT) {
    ans = 0;
    if (t % HeroT != 0) return 0;
    if(j > wad[Hero]) ans = max(ans, wad[Hero]);
    if(q >= ssq[Hero]) {
      int dj2 = (ssp[Hero] == 1 ? -ssd[Hero] : 0);
      if(j+dj2 > 0) ans = max(ans, ssd[Hero]);
    }
  } else {
    if (t % HeroT != 0) return ans = dfs(t+1, j+dj, q+dq, s);
    ans = max(ans, dfs(t+1, j+dj, q+dq+q1[Hero], s));
    ans = max(ans, dfs(t+1, j+dj-wad[Hero], q+dq+q1[Hero], s) + wad[Hero]);
    if(s >= yurun_shen && j < maxjing[Hero]) ans = max(ans, dfs(t+1, min(j+yurun_jing, maxjing[Hero])+dj, q+dq, s-yurun_shen));
    if(s < maxshen[Hero]) ans = max(ans, dfs(t+1, j+dj, q+dq, s+shuerguo_shen));
    if(q >= ssq[Hero]) {
      int dj2 = (ssp[Hero] == 1 ? -ssd[Hero] : 0);
      ans = max(ans, dfs(t+1, j+dj+dj2, q+dq-ssq[Hero], s) + ssd[Hero]);
    }
  }
  return ans;
}

int d[4][4];
vector<string> ans;
int solve(int maxt) {
  for(int h = 0; h < 4; h++)
    for(int p = 1; p <= 3; p++) {
      MaxT = maxt; Hero = h; Pos = p; HeroT = 5 - su[h];
      for(int t = 1; t <= maxt; t++) Hash[t].clear();
      d[h][p] = dfs(1, jing[h], qi[h], shen[h]);
    }
  ans.clear();
  for(int h1 = 0; h1 < 4; h1++)
    for(int h2 = 0; h2 < 4; h2++) if(h2 != h1)
      for(int h3 = 0; h3 < 4; h3++) if(h3 != h1 && h3 != h2)
        if(d[h1][1] + d[h2][2] + d[h3][3] >= SY_jing)
          ans.push_back(name[h1] + name[h2] + name[h3]);
  sort(ans.begin(), ans.end());
  return ans.size();
}

int main() {
  int caseno = 0;
    while(cin >> SY_jing && SY_jing) {
    cin >> XX_su >> SY_su >> yurun_jing >> yurun_shen >> shuerguo_shen;
    for(int i = 0; i < 4; i++)
      cin >> maxjing[i] >> maxshen[i] >> su[i] >> d1x[i] >> d2x[i] >> d1s[i] >> d2s[i] >> wad[i] >> ssd[i] >> ssq[i] >> ssp[i] >> q1[i] >> q2[i] >> jing[i] >> qi[i] >> shen[i];
    XXT = 5 - XX_su; SYT = 5 - SY_su;
    cout << "Case " << ++caseno << ": ";
    for(int i = 1; i <= MAXTIME; i++) if(solve(i)) {
      cout << i;
      for(int j = 0; j < ans.size(); j++) cout << " " << ans[j];
      break;
    }
    if(ans.size() == 0) cout << -1;
    cout << endl << endl;
  }
  return 0;
}
// 25878492	12233	Final Combat	Accepted	C++	0.130	2020-12-23 09:26:25