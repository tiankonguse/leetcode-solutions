/*************************************************************************
    > File Name: move-zeroes.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr  1 02:41:23 2019
 ************************************************************************/

#include "base.h"

class Solution {
 public:
  bool isValid(string s) {
    stack<char> sta;
    map<char, char> m = {{'[', ']'}, {'{', '}'}, {'(', ')'}};
    for (auto c : s) {
      if (m.count(c)) {
        sta.push(m[c]);
      } else {
        if (sta.empty()) {
          return false;
        }
        if (sta.top() != c) {
          return false;
        }
        sta.pop();
      }
    }
    return sta.empty();
  }
};

/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
  TEST_SMP1(Solution, isValid, true, string(""));
  TEST_SMP1(Solution, isValid, false, string("("));
  TEST_SMP1(Solution, isValid, true, string("()"));
  TEST_SMP1(Solution, isValid, false, string("([)"));
  TEST_SMP1(Solution, isValid, false, string("())))"));
  TEST_SMP1(Solution, isValid, true, string("()[]{}"));
  TEST_SMP1(Solution, isValid, false, string("(]"));
  TEST_SMP1(Solution, isValid, false, string("([)]"));
  TEST_SMP1(Solution, isValid, true, string("{[]}"));
  TEST_SMP1(Solution, isValid, false, string("()("));

  return 0;
}
