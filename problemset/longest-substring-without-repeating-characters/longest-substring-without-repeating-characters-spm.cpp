/*************************************************************************
    > File Name: longest-substring-without-repeating-characters-spm.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 25 22:58:03 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int lengthOfLongestSubstring(string str) {
        set<char> s;
        int left = 0, ans = 0;
        for(int i=0;i<str.size();i++){
            while(s.find(str[i]) != s.end()){
                s.erase(str[left++]);
            }
            s.insert(str[i]);
            ans = max(ans, i-left+1);
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

    string first;
    int second;
    int expectAns;

    first = "abcabcbb";
    second = 1;
    expectAns = 3;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = "bbbbb";
    second = 1;
    expectAns = 1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = "pwwkew";
    second = 1;
    expectAns = 3;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
