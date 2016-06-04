/*************************************************************************
  > File Name: remove-nth-node-from-end-of-list.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年06月10日 星期三 23时31分00秒
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
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == NULL){
            return head;
        }

        ListNode root(0);
        root.next = NULL;
        ListNode* now = &root;

        ListNode* nListHead = head;
        ListNode* nListTail = head;
        int nListSize = 1;

        head = head->next;
        nListTail->next = NULL;

        while(head != NULL){
            nListTail->next = head;
            nListTail = nListTail->next;
            nListSize++;
            head = head->next;
            nListTail->next = NULL;

            if(nListSize > n){
                now->next = nListHead;
                nListHead = nListHead->next;
                now = now->next;
                now->next = NULL;

                nListSize--;
            }
        }

        //remove 
        now->next = nListHead->next;
        return root.next;
    }
};
int main() {

    return 0;
}
