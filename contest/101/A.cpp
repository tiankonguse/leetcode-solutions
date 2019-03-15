/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月15日 16:42:37
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

class RLEIterator {
    struct Node {
        Node(int num = 0, int val = 0) {
            this->num = num;
            this->val = val;
        }
        int num;
        int val;
    };
    deque<Node> que;
public:
    RLEIterator(vector<int> A) {
        for(int i=0; i<A.size(); i+=2) {
            que.push_back(Node(A[i], A[i+1]));
        }
    }
    int next(int n) {
        int ans = -1;
        while(!que.empty()) {
            Node node = que.front();
            que.pop_front();
            if(node.num >= n) {
                node.num -= n;
                ans = node.val;
                if(node.num > 0) {
                    que.push_front(node);
                }
                break;
            } else {
                n -= node.num;
            }
        }
        return ans;
    }
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator obj = new RLEIterator(A);
 * int param_1 = obj.next(n);
 */

int main() {
    vector<int> A;
    A = {3,8,0,9,2,5};
    RLEIterator obj(A);
    printf("%d\n",obj.next(2));
    printf("%d\n",obj.next(1));
    printf("%d\n",obj.next(1));
    printf("%d\n",obj.next(2));



    return 0;
}

