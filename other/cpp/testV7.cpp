#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

int main() {
  vector<string> strs = {"00000000000000000081", "00000000000000000145",
                         "00000000000000000158", "00000000000000000077",
                         "00000000000000000145", "00000000000000000145"};
  for (auto v : strs) {
    int i = atoi(v.c_str());
    printf("v=%s i=%d\n", v.c_str(), i);
  }
  return 0;
}