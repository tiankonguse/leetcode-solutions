/*************************************************************************
    > File Name: min-stack.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月22日 星期三 00时58分53秒
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

class MinStack {
    map<int,int>m;
    stack<int>sta;
public:
    void push(int x) {
        sta.push(x);
        if(m.find(x) == m.end()){
            m[x] = 1;
        }else{
            m[x] = m[x] + 1;
        }
    }

    void pop() {
        int x = top();
        sta.pop();

        if(m[x] > 1){
            m[x] = m[x] - 1;
        }else if(m[x] == 1){
            m.erase(x);
        }
    }

    int top() {
        return sta.top();
    }

    int getMin() {
        return m.begin()->first;
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
