/*************************************************************************
    > File Name: middle-of-the-linked-list.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月10日 17:05:56
    > link: https://leetcode.com/problems/middle-of-the-linked-list/
    > No: 876. Middle of the Linked List
    > Contest: 95
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int listLen(ListNode* head){
        int ans = 0;
        while(head){
            ans++;
            head = head->next;
        }
        return ans;
    }
public:
    ListNode* middleNode(ListNode* head) {
        int len = listLen(head)/2;
        while(len>0){
            head = head->next;
            len--;
        }
        return head;
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
