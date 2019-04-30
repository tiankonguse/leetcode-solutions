/*************************************************************************
  > File Name: merge-two-sorted-lists.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年06月11日 星期四 00时11分40秒
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
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
     ListNode(int x) : val(x), next(NULL) {}
 };
class Solution {
    ListNode* sortList(ListNode* l){
        if(l == NULL){
            return l;
        }

        ListNode* head = l;
        ListNode* tail = l;
        ListNode* tmp;

        l = l->next;
        tail->next = NULL;

        while(l != NULL){
            tmp = l;
            l = l->next;
            tmp->next = NULL;

            if(tmp->val <= head->val){
                tmp->next = head;
                head = tmp;
            }else{
                tail->next = tmp;
                tail = tmp;
            }
        }

        return head;
    }
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        l1 = sortList(l1);
        l2 = sortList(l2);

        ListNode root(0);
        ListNode* now = &root;
        now->next = NULL;

        while(l1 != NULL && l2 != NULL){
            if(l1->val < l2->val){
                now->next = l1;
                now = now->next;
                l1 = l1->next;
                now->next = NULL;
            }else{
                now->next = l2;
                now = now->next;
                l2 = l2->next;
                now->next = NULL;
            }
        }

        if(l1 != NULL){
            now->next = l1;
        }else if(l2 != NULL){
            now->next = l2;
        }
        return root.next;
    }
};
int main() {

    return 0;
}
