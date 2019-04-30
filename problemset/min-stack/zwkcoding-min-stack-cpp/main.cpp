/*
 * @Author: zwkcoding
 * @Date: 2019-04-30 20:12:52 
 * @Last Modified by: Zhou WenKai
 * @Last Modified time: 2019-04-30 20:33:55
 */


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

/// Time Complexity: O(n)
/// Space Complexity: O(n)
class MinStack {
    stack<int> original_s;
    stack<int> min_s;
public:
    void push(int x) {
        original_s.push(x);
        if (min_s.empty() || x <= getMin()) min_s.push(x);
    }

    void pop() {
        if (original_s.top() == min_s.top()) min_s.pop();
        original_s.pop();
    }

    int top() {
        return original_s.top();
    }

    int getMin() {
        return min_s.top();
    }
};


struct Node{
    enum{PUSH, POP, TOP, MIN};
    int type;//0 push, 1 pop, 2 top, 3 min 
    int val;// x       NULL    ans    ans
    Node(int type, int val=0):type(type),val(val){

    }
};


void test(){
    srand(time(NULL));
    MinStack minSta;

    vector<Node>vec;

    vec = {
        {Node::PUSH, 4},
        {Node::TOP, 4},
        {Node::MIN, 4},
        {Node::PUSH, 5},
        {Node::TOP, 5},
        {Node::MIN, 4},
        {Node::PUSH, 3},
        {Node::TOP, 3},
        {Node::MIN, 3},
        {Node::POP, 0},
        {Node::TOP, 5},
        {Node::MIN, 4},
    };

    for(vector<Node>::iterator it = vec.begin(); it != vec.end(); it++){
        int type = it->type;
        int val = it->val;
        int ans;

        switch(type){
            case Node::PUSH:
                minSta.push(val);
                printf("PUSH\n");
                break;
            case Node::TOP:
                ans = minSta.top();
                printf("TOP ans = %d val = %d %s\n", ans, val, ans==val?"YES":"NO");
                break;
            case Node::POP:
                minSta.pop();
                printf("POP\n");
                break;
            case Node::MIN:
                ans = minSta.getMin();
                printf("MIN ans = %d val = %d %s\n", ans, val, ans==val?"YES":"NO");
                break;
            default:
                printf("ERROR");
                break;
        }

    }
}

int main(){
    test();
    return 0;
}
