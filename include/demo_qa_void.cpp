/*************************************************************************
    > File Name: B.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月15日 16:42:51
 ************************************************************************/


#include "../../include/base.h"


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

template <class AnsType, class OpreateType,  class DataType1 = int>
void test_qa_void(AnsType& expectAns, OpreateType& opreateParam,DataType1 firstData = DataType1()) {
    AnsType ans;
    StockSpanner work;
    ans.push_back(0);

    for(int i=0; i<firstData.size(); i++) {
        ans.push_back(work.next(firstData[i]));
    }
    int index = getIndex();
    bool check = eq(ans, expectAns);
    if(!check) {
        printf("index %d: NO\n", index);
        output("opreateParam", opreateParam);
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
    vector<int> firstData;
    vector<int> expectAns;

    opreateParam= { "StockSpanner","next","next","next","next","next","next","next" };
    firstData = {{100},{80},{60},{70},{60},{75},{85}};
    expectAns = {0,1,1,1,2,1,4,6};
    test_qa_void(expectAns, opreateParam, firstData);
    return 0;
}

