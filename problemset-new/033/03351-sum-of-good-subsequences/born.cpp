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

#define TASK "3351"

int main(int argc, char** argv) {
  printf("path: %s\n", argv[0]);
  system("pwd");
  system("mkdir -p ./tmp/");
  system("g++ ./data.cpp -std=c++17 " BITS_STDC " -o ./tmp/data.exe -O2");
  system("g++ ./main.cpp -std=c++17 " BITS_STDC " -o ./tmp/main.exe -O2");
  for (int i = 1; i <= 20; ++i) {
    string inFile = "./tmp/data_" TASK "_" + to_string(i) + ".in";
    string outFile = "./tmp/data_" TASK "_" + to_string(i) + ".out";

    string runInData = "./tmp/data.exe > " + inFile;
    string runOutData = "./tmp/main.exe < " + inFile + " > " + outFile;
    int retIn = system(runInData.data());
    printf("born case %d, ret=%d\n", i, retIn);
    int retOut = system(runOutData.data());
    printf("run case %d, ret=%d\n", i, retOut);
  }
  system("zip ./tmp/" TASK ".zip ./tmp/*.in ./tmp/*.out *.cpp");
  return 0;
}