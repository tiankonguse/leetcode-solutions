#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define ll long long
#define ull unsigned long long

int main() {
  system("g++ data.cpp -o data -O2");
  system("g++ force.cpp -o force -O2");
  system("g++ std.cpp -o std -O2");
  for (int i = 1; i <= 100000; ++i) {
    system("./data > data.out");
    auto t1 = steady_clock::now();
    system("./force < data.out > force.out");
    auto t2 = steady_clock::now();
    system("./std < data.out > std.out");
    auto t3 = steady_clock::now();
    auto my = duration_cast<duration<double, ratio<1, 1000> > >(t2 - t1);
    auto it = duration_cast<duration<double, ratio<1, 1000> > >(t3 - t2);
    if (system("diff force.out std.out")) {
      printf("Wrong answer on 测试点#%d\n", i);
      printf("my 用时: %.0lfms\n", my.count());
      printf("it 用时: %.0lfms\n", it.count());
      return 0;
    } else {
      printf("Accepted on 测试点#%d\n", i);
      printf("my 用时: %.0lfms\n", my.count());
      printf("it 用时: %.0lfms\n", it.count());
    }
  }
  return 0;
}