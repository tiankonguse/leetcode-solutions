/*************************************************************************
    > File Name: largest-values-from-labels.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Jun  16 10:24:26 2019
    > link: https://leetcode.com/problems/largest-values-from-labels/
    > No: 1090. Largest Values From Labels
    > Contest: https://leetcode.com/contest/weekly-contest-141
 ************************************************************************/

#include "../../../include/base.h"

template <class T>
using max_queue = priority_queue<T>;

struct Node {
    int value;
    int label;
    Node(int v, int l):value(v),label(l) {
    }

    bool operator<(const Node &t2) const {
        const Node &t1 = *this;

        if(t1.label == t2.label) {
            return t1.value > t2.value;
        } else {
            return t1.label < t2.label;
        }
    }
};

class Solution {

public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int num_wanted, int use_limit) {
        vector<Node> nodes;
        for(int i=0; i<values.size(); i++) {
            nodes.push_back(Node(values[i], labels[i]));
        }
        sort(nodes.begin(), nodes.end());

        max_queue<int> que;

        int preLabel = nodes[0].label;
        int preNum = 1;
        que.push(nodes[0].value);
        for(int i=1; i<nodes.size(); i++) {
            if(nodes[i].label != preLabel) {
                que.push(nodes[i].value);
                preLabel = nodes[i].label;
                preNum = 1;
            } else {
                if(preNum < use_limit) {
                    que.push(nodes[i].value);
                    preNum++;
                }
            }
        }

        int ans = 0;
        int wantedNum = 0;
        while(!que.empty() && wantedNum < num_wanted) {
            ans += que.top();
            //printf("wantedNum=%d val=%d\n", wantedNum, que.top());
            wantedNum++;
            que.pop();
        }
        return ans;
    }
};
/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
#define CLASS Solution
#define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
