#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    int getLen(ListNode* head){
        int ans = 0;
        while(head != NULL){
            head = head->next;
            ans++;
        }
        return ans;
    }
    ListNode* getNode(ListNode* head, int a){
        int ans = 0;
        
        while(head != NULL){
            ans++;
            if(ans == a){
                return head;
            }
            head = head->next;
        }
        return head;
    }
public:
    ListNode* swapNodes(ListNode* head, int a) {
        if(head == NULL || head->next == NULL) return head;
        int len = getLen(head);
        
        int b = len + 1 - a;
        if(a == b){
            return head; // 中间节点
        }
        
        if(a > b){
            swap(a, b);
        }
        
        // a < b
        
        ListNode* pa = getNode(head, a);
        ListNode* pb = getNode(head, b);
        swap(pa->val, pb->val);
        return head;
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
