/*************************************************************************
    > File Name: linked-list-cycle-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月04日 星期六 14时48分58秒
 ************************************************************************/

#include<stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(){

    }
    ListNode(int x) : val(x), next(NULL) {}
    void init(int x, ListNode* next){
        this->val = x;
        this->next = next;
    }
};
class Solution {

public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* first = head;
        if(first == NULL){
            return NULL;
        }

        int num = 1;
        ListNode* second = first->next;
        if(second == NULL){
            return NULL;
        }
        first = first->next;
        second = second->next;

        //printf("first step\n");
        //printf("head=%p first=%p second=%p\n", head, first, second);
        
        while(first != second && first != NULL && second != NULL){
            num++;
            first = first->next;
            second = second->next;
            if(second == NULL){
                return NULL;
            }
            second = second->next;
        }

        if(first == NULL || second == NULL){
            return NULL;
        }


        // now have cycle
        //
        //printf("now have cycle\n");
        //printf("head=%p first=%p second=%p\n", head, first, second);
        first = head;
        while(first != second){
            //printf("first=%p val=%d second=%p val=%d\n", first, first->val, second, second->val);

            if(second == head){
                return head;
            }
            first = first->next;
            second = second->next;
        }
        return first;
    }
};

void test(){
    Solution work;
    ListNode list[10];
    for(int i=0;i<8;i++){
        list[i].init(i, list+i+1);
    }
    list[3].next = list+1;
   
    for(int i=0;i<8;i++){
        //printf("%p val=%d next=%p next-val=%d\n", list + i, list[i].val, list[i].next, list[i].next->val);
    }

    ListNode* ans = work.detectCycle(list);
    if(ans == NULL){
        printf("NULL\n");
    }else{
        printf("%p %d\n", ans, ans->val);

    }

}

int main(){
    test();
    return 0;
}
