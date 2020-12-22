// 例题2  数三角形（Triangle Counting, UVa11401）
// Rujia Liu
#include<iostream>
using namespace std;

long long f[1000010]; // int存不下
int main() {
  f[3] = 0;
  for(long long x = 4; x <= 1000000; x++)
    f[x] = f[x-1] + ((x-1)*(x-2)/2 - (x-1)/2)/2; // 递推

  int n;
  while(cin >> n) {
    if(n < 3) break;
    cout << f[n] << endl;    
  }
  return 0;
}
// 25877025 11401 Triangle Counting Accepted C++ 0.020 2020-12-23 01:22:22