#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define ll long long
#define ull unsigned long long

#define PRJ_ROOT_PATH "../../"

#ifdef USACO_LOCAL_JUDGE
#define BITS_STDC " -I" PRJ_ROOT_PATH "include/ "
#define CODE_PATH PRJ_ROOT_PATH "other/NOI/1998/1.scarf-cutting/"
#define CODE_DATA CODE_PATH "scarf-cutting-data.cpp"
#define CODE_FORCE CODE_PATH "elainya_stars-scarf-cutting.cpp"
#define CODE_MAIN CODE_PATH "scarf-cutting.cpp"
#else
#define BITS_STDC " "
#define CODE_PATH ""
#endif

int main(int argc, char** argv) {
  system("mkdir -p ./tmpfile");
  system("g++ " CODE_DATA " -std=c++17 " BITS_STDC " -o ./tmpfile/data.exe -O2");
  system("g++ " CODE_FORCE " -std=c++17 " BITS_STDC "  -o ./tmpfile/force.exe -O2");
  // system("go build  -o ./tmpfile/force.exe " CODE_FORCE);
  system("g++ " CODE_MAIN " -std=c++17 -D_GLIBCXX_DEBUG -fsanitize=address,undefined -fno-omit-frame-pointer " BITS_STDC " -o ./tmpfile/main.exe -O2");
  
  for (int i = 1; i <= 1000; ++i) {
    system("./tmpfile/data.exe > ./tmpfile/data.out");
    system("echo > ./tmpfile/force.out"); 
    system("echo > ./tmpfile/main.out");
    auto t1 = steady_clock::now();
    int ret1 = system("./tmpfile/force.exe < ./tmpfile/data.out > ./tmpfile/force.out");
    assert(ret1==0);
    auto t2 = steady_clock::now();
    system("./tmpfile/main.exe < ./tmpfile/data.out > ./tmpfile/main.out");
    auto t3 = steady_clock::now();
    auto force = duration_cast<duration<double, ratio<1, 1000> > >(t2 - t1);
    auto main = duration_cast<duration<double, ratio<1, 1000> > >(t3 - t2);
    if (system("diff ./tmpfile/force.out ./tmpfile/main.out")) {
      printf("Wrong answer on 测试点#%d\n", i);
      printf("force 用时: %.0lfms\n", force.count());
      printf("main 用时: %.0lfms\n", main.count());
      return 0;
    } else {
      printf("Accepted on 测试点#%d\n", i);
      printf("force 用时: %.0lfms\n", force.count());
      printf("main 用时: %.0lfms\n", main.count());
    }
  }
  return 0;
}