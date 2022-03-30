/*************************************************************************
    > File Name: implement-queue-using-stacks.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr  8 23:23:04 2019
 ************************************************************************/

#include "../../include/base.h"

class MyQueue {
    stack<int> sta;
    int first;

    void popo(stack<int>& from, stack<int>&to) {
        while(!from.empty()) {
            to.push(from.top());
            from.pop();
        }
    }

public:
    /** Initialize your data structure here. */
    MyQueue() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        if(sta.empty()) {
            first = x;
        }
        sta.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        stack<int> tmpSta;
        popo(sta, tmpSta);
        int ans = first;
        tmpSta.pop();

        if(!tmpSta.empty()) {
            first = tmpSta.top();
        }
        popo(tmpSta, sta);
        return ans;
    }

    /** Get the front element. */
    int peek() {
        return first;
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return sta.empty();
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
    MyQueue work;

    for(int i=0; i<opreateParam.size(); i++) {
        int ansTmp = -1;
        if(opreateParam[i] == "push") {
            work.push(firstData[i]);
        }
        if(opreateParam[i] == "pop") {
            ansTmp = work.pop();
        }
        if(opreateParam[i] == "peek") {
            ansTmp = work.peek();
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

    opreateParam= {"push","push","peek","pop","empty"};
    initData = {};
    firstData = {{1},{2},{-1},{-1},{-1}};
    expectAns = {{-1},{-1},{1},{1},{0} };
    test_qa(expectAns, opreateParam, initData, firstData);

    return 0;
}


