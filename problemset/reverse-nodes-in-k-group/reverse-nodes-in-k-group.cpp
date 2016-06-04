/*************************************************************************
  > File Name: reverse-nodes-in-k-group.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年05月21日 星期四 22时49分50秒
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
     ListNode(int x = 0) : val(x), next(NULL) {}
 };
class Solution {
public:
    ListNode* reverseKGroup(ListNode* list, int k) {
        ListNode head(0);
        ListNode *tail = &head;
        ListNode* kHead, *kTail;
        ListNode* tmpPoint;
        int i;

        while(list != NULL){
            kHead = kTail = list;
            list = list->next;
            
            kTail->next = NULL;

            for(i=1;i<k && list != NULL;i++){
                kTail->next = list;
                kTail = list;
                list = list->next;
                kTail->next = NULL;
            }

            if(i == k){
                kTail = kHead;

                while(kHead != NULL){
                    tmpPoint = kHead;
                    kHead = kHead->next;

                    tmpPoint->next = tail->next;
                    tail->next = tmpPoint;
                }

                tail = kTail;
            }else{
                tail->next = kHead;
                tail = kTail;
            }

        }

        return head.next;
    }
};
void output(char const*name, ListNode* list){
    printf("%s ",name);
    while(list != NULL){
        printf("%d->", list->val);
        list = list->next;
    }
    printf("null\n");
}
int main() {
    
    Solution work;
    ListNode list[10](0);
    ListNode* ans;
    int k;

    for(int i=0;i<5;i++){
        list[i] = i + 1;
        list[i].next = list + i + 1;
    }
    list[4].next = NULL;

    output("input:", list);
    k = 2;
    printf("k=%d\n",k);
    ans = work.reverseKGroup(list, k);
    output("output:", ans);

    for(int i=0;i<5;i++){
        list[i] = i + 1;
        list[i].next = list + i + 1;
    }
    list[4].next = NULL;

    output("input:", list);
    k = 3;
    printf("k=%d\n",k);
    ans = work.reverseKGroup(list, k);
    output("output:", ans);

    return 0;
}
