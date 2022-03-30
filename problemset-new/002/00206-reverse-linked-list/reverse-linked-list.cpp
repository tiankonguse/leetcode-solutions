/*************************************************************************
  > File Name: reverse-linked-list.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年06月 7日 20:28:55
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
     ListNode(int x=0) : val(x), next(NULL) {}
 };
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode root(0);
        ListNode* next;

        while(head != NULL){
            next = head->next;
            head->next = root.next;
            root.next = head;
            head = next;
        }
        return root.next;
    }
};

int main() {
    
    return 0;
}
