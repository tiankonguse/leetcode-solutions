#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define ll long long
#define ull unsigned long long

#define PRJ_ROOT_PATH "../../"

#ifdef USACO_LOCAL_JUDGE
#define BITS_STDC " -I" PRJ_ROOT_PATH "include/ "
#define CODE_PATh \
  PRJ_ROOT_PATH "other/luogu/contest/212/"
#define CODE_DATA CODE_PATh "C-data.cpp"
#define CODE_FORCE CODE_PATh "C-v22.cpp"
#define CODE_MAIN CODE_PATh "C-v3.cpp"
#else
#define BITS_STDC " "
#define CODE_PATh ""
#endif

int main(int argc, char** argv) {
  system("mkdir -p ./tmpfile");
  system("g++ " CODE_DATA " -std=c++17 " BITS_STDC " -o ./tmpfile/data.exe -O2");
  system("g++ " CODE_FORCE " -std=c++17 " BITS_STDC "  -o ./tmpfile/force.exe -O2");
  system("g++ " CODE_MAIN " -std=c++17 " BITS_STDC " -o ./tmpfile/main.exe -O2");
  
  for (int i = 1; i <= 1000; ++i) {
    system("./tmpfile/data.exe > ./tmpfile/data.out");
    auto t1 = steady_clock::now();
    system("./tmpfile/force.exe < ./tmpfile/data.out > ./tmpfile/force.out");
    auto t2 = steady_clock::now();
    system("./tmpfile/main.exe < ./tmpfile/data.out > ./tmpfile/main.out");
    auto t3 = steady_clock::now();
    auto my = duration_cast<duration<double, ratio<1, 1000> > >(t2 - t1);
    auto it = duration_cast<duration<double, ratio<1, 1000> > >(t3 - t2);
    if (system("diff ./tmpfile/force.out ./tmpfile/main.out")) {
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