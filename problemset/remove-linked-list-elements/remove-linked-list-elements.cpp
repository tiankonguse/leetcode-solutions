/*************************************************************************
    > File Name: remove-linked-list-elements.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月25日 星期六 16时44分46秒
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
    int val;

    void solver(ListNode* root){
        ListNode* pre = root;
        ListNode* now = root->next;

        while(now != NULL){
            if(now->val == val){
                now = now->next;
                pre->next = now;
            }else{
                pre = now;
                now = now->next;
            }
        }
    }

public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode root(0);
        root.next = head;
        this->val = val;
        solver(&root);
        return root.next;
    }
};


void output(ListNode* root){
    while(root != NULL){
        printf("%d -> ", root->val);
        root = root->next;
    }
    printf("NULL\n");
}

void borndata(vector<int>&data, ListNode* list){
    for(int i=0;i<data.size();i++){
        list[i].val = data[i];
        list[i].next = list + i + 1;
    }
    if(data.size()){
        list[data.size()-1].next = NULL;
    }
}

void test(){
    srand(time(NULL));
    Solution work;

    ListNode list[100];
    vector<int>data;
    ListNode* ans;
    int val;

    data = {1, 2, 6, 3, 4, 5, 6};
    val = 6;
    borndata(data, list);
    output(list);
    ans = work.removeElements(list, val);
    output(ans);

}

int main(){
    test();
    return 0;
}
