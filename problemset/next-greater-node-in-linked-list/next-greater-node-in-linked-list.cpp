/*************************************************************************
    > File Name: next-greater-node-in-linked-list.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 22:45:30 2019
    > contest: https://leetcode.com/contest/weekly-contest-130
    > link: https://leetcode.com/problems/next-greater-node-in-linked-list/  
 ************************************************************************/

#include "../../include/base.h"


class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> ans;
        map<int, vector<int> > valToIndex;
        int index = 0, val = 0;
        while(head != nullptr) {
            ans.push_back(0);
            val = head->val;
            head = head->next;

            while(valToIndex.size() > 0 && valToIndex.begin()->first < val) {
                auto& tmpVec = valToIndex.begin()->second;
                for(int i=0; i<tmpVec.size(); i++) {
                    ans[tmpVec[i]] = val;
                }
                valToIndex.erase(valToIndex.begin());
            }

            if(valToIndex.begin()->first == val) {
                auto& tmpVec = valToIndex.begin()->second;
                tmpVec.push_back(index);
            } else {
                valToIndex[val].push_back(index);
            }


            index++;
        }
        return ans;
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
    vector<int> first;
    vector<int> expectAns;
    ListNode root[100];

    first = {2,1,5};
    expectAns = {5,5,0};
    TEST_SMP1(Solution, nextLargerNodes, expectAns, born(first, root));

    first = {2,7,4,3,5};
    expectAns = {7,0,5,5,0};
    TEST_SMP1(Solution, nextLargerNodes, expectAns, born(first, root));

    first = {1,7,5,1,9,2,5,1};
    expectAns = {7,9,9,9,0,5,0,0};
    TEST_SMP1(Solution, nextLargerNodes, expectAns, born(first, root));


    first = {2,1, 1,5};
    expectAns = {5,5,5,0};
    TEST_SMP1(Solution, nextLargerNodes, expectAns, born(first, root));

    return 0;
}
