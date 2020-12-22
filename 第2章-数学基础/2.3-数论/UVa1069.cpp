// 例题8  总是整数（Always an Integer, World Finals 2008, UVa1069）
// 陈锋
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Polynomial {
  vector<int> a, p;                     //第i项为a[i] * n^p[i]
  void parse_polynomial(string expr) {  //解析多项式（不带括号）
    int i = 0, len = expr.size();
    while (i < len) {  //每次循环体解析一个a * n^p
      int sign = 1, v = 0;
      if (expr[i] == '+') i++;
      if (expr[i] == '-') sign = -1, i++;
      while (i < len && isdigit(expr[i])) v = v * 10 + expr[i++] - '0';
      //系数的绝对值
      if (i == len) {
        a.push_back(v), p.push_back(0);
        continue;
      }  //常数项
      assert(expr[i] == 'n');
      if (v == 0) v = 1;  //无系数，按1处理
      v *= sign;
      if (expr[++i] == '^') {   //有指数项
        a.push_back(v), v = 0;  //清空v，接下来用v保存指数
        i++;
        while (i < len && isdigit(expr[i])) v = v * 10 + expr[i++] - '0';
        p.push_back(v);
      } else  //无指数项
        a.push_back(v), p.push_back(1);
    }
  }

  // 计算f(x)除以MOD的余数
  int mod(int x, int MOD) {
    int ans = 0;
    for (size_t i = 0; i < a.size(); i++) {
      int m = a[i];
      for (int j = 0; j < p[i]; j++) m = (LL)m * x % MOD;
      //注意避免溢出
      ans = ((LL)ans + m) % MOD;  //加法也可能会溢出。
    }
    return ans;
  }
};

bool check(string expr) {
  int p = expr.find('/');
  Polynomial poly;
  poly.parse_polynomial(expr.substr(1, p - 2));
  int D = atoi(expr.substr(p + 1).c_str());
  for (int i = 1; i <= poly.p[0] + 1; i++)
    if (poly.mod(i, D) != 0) return false;
  return true;
}

int main() {
  string expr;
  for (int kase = 1; cin >> expr; kase++) {
    if (expr[0] == '.') break;
    printf("Case %d: ", kase);
    if (check(expr))
      puts("Always an integer");
    else
      puts("Not always an integer");
  }
  return 0;
}
// Accepted 70ms 1829 C++5.3.0 2020-12-12 16:16:22 25838756