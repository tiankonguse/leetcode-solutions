#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define ll long long
#define ull unsigned long long

#ifdef USACO_LOCAL_JUDGE
#define BITS_STDC \
  " -I/Users/tiankonguse/project/github/leetcode-solutions/include/ "
#else
#define BITS_STDC " "
#endif

int main(int argc, char** argv) {
  system("g++ ./data.cpp -std=c++17 " BITS_STDC " -o data.exe -O2");
  system("g++ ./force.cpp -std=c++17 " BITS_STDC "  -o force.exe -O2");
  system("g++ ./main.cpp -std=c++17 " BITS_STDC " -o main.exe -O2");
  for (int i = 1; i <= 100; ++i) {
    system("./data.exe > data.out");
    auto t1 = steady_clock::now();
    system("./force.exe < data.out > force.out");
    auto t2 = steady_clock::now();
    system("./main.exe < data.out > main.out");
    auto t3 = steady_clock::now();
    auto my = duration_cast<duration<double, ratio<1, 1000> > >(t2 - t1);
    auto it = duration_cast<duration<double, ratio<1, 1000> > >(t3 - t2);
    if (system("diff force.out main.out")) {
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