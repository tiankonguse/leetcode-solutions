/*************************************************************************
    > File Name: top-k-frequent-elements.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 25 23:18:52 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (int num : nums) {
            ++m[num];
        }
        vector<vector<int>> buckets(nums.size() + 1);
        for (auto p : m){
            buckets[p.second].push_back(p.first);
        }

        vector<int> ans;
        for (int i = buckets.size() - 1; i >= 0 && ans.size() < k; --i) {
            for (int num : buckets[i]) {
                ans.push_back(num);
                if (ans.size() == k)
                    break;
            }
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
#define FUNCTION topKFrequent

    vector<int> first;
    int second;
    vector<int> expectAns;

    first = {1,1,1,2,2,3};
    second = 2;
    expectAns = {1,2};
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {1};
    second = 1;
    expectAns = {1};
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
