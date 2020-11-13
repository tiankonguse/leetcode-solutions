/*************************************************************************
    > File Name: longest-substring-without-repeating-characters-spm.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 25 22:58:03 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "base.h"

class Solution {
 public:
  int lengthOfLongestSubstring(string str) {
    unordered_set<char> s;
    int left = 0, ans = 0;
    for (int i = 0; i < str.size(); i++) {
      while (s.count(str[i])) {
        s.erase(str[left++]);
      }
      s.insert(str[i]);
      ans = max(ans, i - left + 1);
    }
    return ans;
  }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;


    first = 1;
    second = 1;
    expectAns = 1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);
*/
int main() {
#define CLASS Solution
#define FUNCTION lengthOfLongestSubstring

  TEST_SMP1(CLASS, FUNCTION, 3, "abcabcbb");

  TEST_SMP1(CLASS, FUNCTION, 1, "bbbbb");

  TEST_SMP1(CLASS, FUNCTION, 3, "pwwkew");

  return 0;
}
