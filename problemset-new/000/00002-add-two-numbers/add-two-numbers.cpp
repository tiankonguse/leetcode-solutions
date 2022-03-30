/*************************************************************************
    > File Name: add-two-numbers.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月17日 星期五 21时54分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;


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
    ListNode(int x=0) : val(x), next(NULL) {}
};
class Solution {
    queue<ListNode*> que;
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        free();
        ListNode root(0);
        int sum = 0;
        ListNode* tail = &root;

        while(l1 != NULL || l2 != NULL || sum != 0){
            if(l1 != NULL){
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2 != NULL){
                sum += l2->val;
                l2 = l2->next;
            }
            tail->next = new ListNode(sum%10);
            tail = tail->next;
            que.push(tail);
            sum /= 10;
        }

        return root.next;
    }
    void free(){
        while(!que.empty()){
            delete que.front();
            que.pop();
        }
    }
    ~Solution(){
        free();
    }
};


void output(ListNode* root){
    printf("root -> ");
    while(root != NULL){
        printf("%d(%p) -> ", root->val, root);
        root = root->next;
    }
    printf("%p\n", root);
}

void test(){
    srand(time(NULL));
    Solution work;
    ListNode* ans;
    ListNode list[100];
    ListNode* first;
    ListNode* second;

    list[0].val = 2; list[0].next = list + 1; 
    list[1].val = 4; list[1].next = list + 2;
    list[2].val = 3; list[2].next = NULL;
    

    list[3].val = 5; list[3].next = list + 4;
    list[4].val = 6; list[4].next = list + 5;
    list[5].val = 4; list[5].next = NULL;

    first = list;
    second = list + 3;
    output(first);
    output(second);
    ans = work.addTwoNumbers(first, second);
    output(ans);

}

int main(){
    test();
    return 0;
}
