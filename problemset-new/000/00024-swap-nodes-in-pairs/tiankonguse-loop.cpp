/*************************************************************************
    > File Name: swap-nodes-in-pairs.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat May 25 22:39:45 2019
    > link: https://leetcode.com/problems/swap-nodes-in-pairs/
    > No: 24. Swap Nodes in Pairs
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        if(!head || !head->next)return head;

        ListNode* ans = head->next;
        ListNode* pre = NULL;
        while(head && head->next){
            ListNode* tmp = head->next;
            head->next = tmp->next;
            tmp->next = head;

            if(pre)pre->next = tmp;
            pre = head;
            head = head->next;
        }
        return ans;
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
