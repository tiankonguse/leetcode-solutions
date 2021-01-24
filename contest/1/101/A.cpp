/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月15日 16:42:37
 ************************************************************************/


#include "../../include/base.h"


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

template <class AnsType, class OpreateType, class InitType, class DataType1 = int>
void test_qa(AnsType& expectAns, OpreateType& opreateParam, InitType& initData, DataType1 firstData = DataType1()) {
    AnsType ans;
    RLEIterator work(initData);
    ans.push_back(0);

    for(int i=0; i<firstData.size(); i++) {
        ans.push_back(work.next(firstData[i]));
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

    opreateParam= { "RLEIterator","next","next","next","next" };
    initData = {3,8,0,9,2,5};
    firstData = {{2},{1},{1},{2}};
    expectAns = {0,8,8,5,-1};
    test_qa(expectAns, opreateParam, initData, firstData);




    return 0;
}

