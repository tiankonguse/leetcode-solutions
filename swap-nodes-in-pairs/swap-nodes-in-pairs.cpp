/*************************************************************************
    > File Name: swap-nodes-in-pairs.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月06日 星期一 13时55分46秒
 ************************************************************************/

#include<stdio.h>

/**
 * Definition for singly-linked list.
 */
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(){

     }
     ListNode(int x) : val(x), next(NULL) {}
 };
class Solution {

    void swap(ListNode* head){
        ListNode* first;
        ListNode* second;
        while(head->next != NULL && head->next->next != NULL){
            first = head->next;
            second = first->next;
            
            head->next = second;
            first->next = second->next;
            second->next = first;

            head = first;
        }
    }

public:
    ListNode *swapPairs(ListNode *head) {
        ListNode first(0);
        first.next = head;
        swap(&first);
        return first.next;
    }
};


void output(ListNode* head){
    while(head != NULL){
        printf("%d->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

void test(){ 
    Solution work;
    ListNode list[10];
    for(int i=1;i<=4;i++){
        list[i].next = list + i + 1;
        list[i].val = i;
    }
    list[4].next = NULL;
    output(list+1);
    ListNode* ans = work.swapPairs(list+1);
    output(ans);
}

int main(){
    test();
    return 0;
}
