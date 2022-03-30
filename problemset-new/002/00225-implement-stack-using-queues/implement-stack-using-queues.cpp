/*************************************************************************
    > File Name: implement-stack-using-queues.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr  8 23:51:14 2019
 ************************************************************************/

#include "../../include/base.h"

class MyStack {
    queue<int> que;
    int last;

    void popo(queue<int>& from, queue<int>&to) {
        while(!from.empty()) {
            to.push(from.front());
            from.pop();
        }
    }
public:
    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x onto stack. */
    void push(int x) {
        que.push(x);
        last = x;
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        queue<int> tmpQue;
        while(que.size() > 1) {
            last = que.front();
            tmpQue.push(que.front());
            que.pop();
        }
        swap(tmpQue, que);
        return tmpQue.front();
    }

    /** Get the top element. */
    int top() {
        return last;
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return que.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
template <class AnsType, class OpreateType, class InitType, class DataType1 = int>
void test_qa(AnsType& expectAns, OpreateType& opreateParam, InitType& initData, DataType1 firstData = DataType1()) {
    AnsType ans;
    MyStack work;

    for(int i=0; i<opreateParam.size(); i++) {
        int ansTmp = -1;
        if(opreateParam[i] == "push") {
            work.push(firstData[i]);
        }
        if(opreateParam[i] == "pop") {
            ansTmp = work.pop();
        }
        if(opreateParam[i] == "top") {
            ansTmp = work.top();
        }
        if(opreateParam[i] == "empty") {
            ansTmp = work.empty();
        }
        ans.push_back(ansTmp);
    }
    int index = getIndex();
    bool check = eq(ans, expectAns);
    if(!check) {
        printf("index %d: NO\n", index);
        output("opreateParam", opreateParam);
        output("initData", initData);
        output("firstData", firstData);
        output("ans", ans);
        output("expectAns", expectAns);

    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");
}

int main() {
    vector<string> opreateParam;
    vector<int> initData;
    vector<int> firstData;
    vector<int> expectAns;

    opreateParam= {"push","push","top","pop","empty"};
    initData = {};
    firstData = {{1},{2},{-1},{-1},{-1}};
    expectAns = {{-1},{-1},{2},{2},{0} };
    test_qa(expectAns, opreateParam, initData, firstData);

    return 0;
}


