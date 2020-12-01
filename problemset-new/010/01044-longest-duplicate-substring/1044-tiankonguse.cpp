/*************************************************************************
    > File Name: longest-duplicate-substring.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 12 10:29:17 2019
    > link: https://leetcode.com/problems/longest-duplicate-substring/
    > No: 1044. Longest Duplicate Substring
    > Contest: https://leetcode.com/contest/weekly-contest-136
 ************************************************************************/

#include "../../include/base.h"



typedef unsigned long long ULL;
class Solution {
    //Rabin-Karp 's algorithm
    int check(int mid, string& S) {
        set<ULL> s;

        ULL now = 0;
        ULL base = 1;
        for(int i=0; i<mid; i++) {
            now = now * 26 + (S[i] - '0');
            base *= 26;
        }
        s.insert(now);
        //printf("mid=%d\n%d=%llu\n", mid, mid-1, now);

        for(int i=mid; i<S.length(); i++) {
            now = now*26 + (S[i] - '0') - (S[i - mid] - '0') * base;
            //printf("%d=%llu\n", i, now);
            if(s.find(now) != s.end()) {
                //printf("FIND\n");
                return i - mid + 1;
            }
            s.insert(now);
        }
        //printf("NO FIND\n");
        return -1;
    }
public:
    string longestDupSubstring(string& S) {
        int left = 1, right = S.length();

        int ansPos = 0;
        int ansLen = 0;
        while(left < right) {
            int mid = (left + right)/2;
            int startPos = check(mid, S);
            if(startPos != -1) {
                ansPos = startPos;
                ansLen = mid;
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return  S.substr(ansPos, ansLen);
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());

    // dir : up, right, down, right
    //int dir[4][2] = {{0,1}},{1,0},{0,-1,{-1,0}};
*/
int main() {
#define CLASS Solution
#define FUNCTION longestDupSubstring

    string first;
    string expectAns;

    first = "banana";
    expectAns = "ana";
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = "abcd";
    expectAns = "";
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
