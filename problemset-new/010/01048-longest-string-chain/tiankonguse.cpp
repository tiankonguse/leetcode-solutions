/*************************************************************************
    > File Name: longest-string-chain.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 19 10:27:35 2019
    > link: https://leetcode.com/problems/longest-string-chain/
    > No: 1048. Longest String Chain
    > Contest: https://leetcode.com/contest/weekly-contest-137
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
    vector<vector<int>> next;
    vector<int> ans;

    bool isPre(vector<string>& words, int one, int two) {
        if(words[one].size() + 1 != words[two].size()) {
            return false;
        }
        int onePos = 0, twoPos = 0;
        while(onePos < words[one].size() && words[one][onePos] == words[two][twoPos]) {
            onePos++, twoPos++;
        }
        if(onePos == words[one].size()) {
            return true;
        }
        twoPos++;
        while(onePos < words[one].size() && words[one][onePos] == words[two][twoPos]) {
            onePos++, twoPos++;
        }
        if(onePos == words[one].size()) {
            return true;
        }
        return false;
    }

    int dfs(vector<string>& words, int nowPos) {
        if(ans[nowPos] != -1) {
            return ans[nowPos];
        }
        int maxAns = 0;
        for(int i=0; i<next[nowPos].size(); i++) {
            maxAns = max(maxAns, dfs(words, next[nowPos][i]));
        }
        return ans[nowPos] = maxAns + 1;
    }

public:
    int longestStrChain(vector<string>& words) {
        next.resize(words.size());
        for(int i=0; i<words.size(); i++) {
            for(int j=0; j<words.size(); j++) {
                if(i==j)
                    continue;
                if(isPre(words, i, j)) {
                    next[i].push_back(j);
                }
            }
        }

        int maxAns = 0;
        ans.resize(words.size(), -1);
        for(int i=0; i<words.size(); i++) {
            dfs(words, i);
            maxAns = max(maxAns, ans[i]);
        }
        return maxAns;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
#define CLASS Solution
#define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
