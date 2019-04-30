/*************************************************************************
    > File Name: group-anagrams.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Apr 24 00:24:23 2019
    > link: https://leetcode.com/problems/group-anagrams/
    > No: 49. Group Anagrams
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string> >m;
        for(int i=0; i<strs.size(); i++) {
            string key = strs[i];
            sort(key.begin(),key.end());
            m[key].push_back(strs[i]);
        }
        vector<vector<string>> ans;
        for(auto& p : m) {
            ans.push_back(p.second);
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
#define FUNCTION groupAnagrams

    vector<string> first;
    int second;
    vector<vector<string>>  expectAns;

    first = {"eat", "tea", "tan", "ate", "nat", "bat"};
    second = 1;
    expectAns = {
        {"ate","eat","tea"},
        {"nat","tan"},
        {"bat"}
    };
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
