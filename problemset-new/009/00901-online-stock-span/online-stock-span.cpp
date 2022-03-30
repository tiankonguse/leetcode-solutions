/*************************************************************************
    > File Name: online-stock-span.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月15日 16:42:51
 ************************************************************************/

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<time.h>
#include "../../include/base.h"
using namespace std;


#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;
auto __ =[]() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}
();

class StockSpanner {
    struct Node {
        Node(int num = 0, int val = 0) {
            this->num = num;
            this->val = val;
        }
        int num;
        int val;
    };
    stack<Node> sta;
public:
    StockSpanner() {

    }
    int next(int price) {
        int ans = 1;
        while(!sta.empty() && sta.top().val <= price) {
            ans += sta.top().num;
            sta.pop();
        }
        sta.push(Node(ans, price));
        return ans;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner obj = new StockSpanner();
 * int param_1 = obj.next(price);
 */


int main() {
    StockSpanner obj;
    printf("%d\n",obj.next(100));
    printf("%d\n",obj.next(80));
    printf("%d\n",obj.next(60));
    printf("%d\n",obj.next(70));
    printf("%d\n",obj.next(60));
    printf("%d\n",obj.next(75));
    printf("%d\n",obj.next(85));

    return 0;
}

