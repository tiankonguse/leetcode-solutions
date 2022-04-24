/*************************************************************************
    > File Name: reverse-words-in-a-string.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr  1 01:55:36 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
  string removeSpaces(string s) {
    string ans;
    int index = 0;
    while (index < s.size()) {
      while (index < s.size() && s[index] != ' ') ans.push_back(s[index++]);
      while (index < s.size() && s[index] == ' ') index++;
      if (index < s.size() && ans.size() > 0) ans.push_back(' ');
    }
    return ans;
  }

 public:
  string reverseWords(string s) {
    s = removeSpaces(s);
    auto start = s.begin();
    for (auto it = s.begin(); it != s.end();) {
      while (it != s.end() && *it != ' ') {
        it++;
      }
      std::reverse(start, it);
      if (it == s.end()) break;
      it++;  // skip space
      start = it;
    }
    std::reverse(s.begin(), s.end());
    return s;
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
  string first;
  string expectAns;

  first = "the sky is blue";
  expectAns = "blue is sky the";
  TEST_SMP1(Solution, reverseWords, expectAns, first);

  first = "  hello world!  ";
  expectAns = "world! hello";
  TEST_SMP1(Solution, reverseWords, expectAns, first);

  first = "a good   example";
  expectAns = "example good a";
  TEST_SMP1(Solution, reverseWords, expectAns, first);

  return 0;
}
