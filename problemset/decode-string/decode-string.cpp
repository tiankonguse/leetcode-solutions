/*************************************************************************
    > File Name: decode-string.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr  9 00:03:52 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    string dfs(string& s, int& left) {
        string ans;
        int k = 0;
        while(left < s.length()) {
            char val = s[left++];
            if(val >= '0' && val <= '9') {
                k = k * 10 + val - '0';
            } else if(val == '[') {
                string tmpAns = dfs(s, left);
                while(k>0) {
                    k--;
                    ans += tmpAns;
                }
            } else if(val == ']') {
                break;
            } else {
                ans.push_back(val);
            }
        }
        return ans;
    }
public:
    string decodeString(string s) {
        int left = 0;
        return dfs(s, left);
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

    first = "3[a]2[bc]";
    expectAns = "aaabcbc";
    TEST_SMP1(Solution, decodeString, expectAns, first);

    first = "3[a2[c]]";
    expectAns = "accaccacc";
    TEST_SMP1(Solution, decodeString, expectAns, first);

    first = "2[abc]3[cd]ef";
    expectAns = "abcabccdcdcdef";
    TEST_SMP1(Solution, decodeString, expectAns, first);


    return 0;
}
