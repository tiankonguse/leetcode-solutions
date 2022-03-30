/*************************************************************************
    > File Name: perfect-squares.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr  2 00:32:50 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int numSquares(int n) {
        vector<int> squares;
        for(int i=1; i<=n; i++) {
            if(i*i >n)
                break;
            squares.push_back(i*i);
        }

        set<int> have;
        queue<pair<int,int>> que;
        que.push(make_pair(0,0));
        have.insert(0);

        while(!que.empty()) {
            auto p = que.front();
            que.pop();
            for(int i=0; i<squares.size(); i++) {
                int val = p.first + squares[i];
                if(val == n) {
                    return p.second + 1;
                }
                if(val > n){
                    continue;
                }
                if(have.find(val) != have.end()) {
                    continue;
                }
                que.push(make_pair(val,p.second+1));
                have.insert(val);
            }
        }
        return 0;
    }
};

/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    int first;
    int expectAns;

    first = 12;
    expectAns = 3;
    TEST_SMP1(Solution, numSquares, expectAns, first);

    first = 13;
    expectAns = 2;
    TEST_SMP1(Solution, numSquares, expectAns, first);

    return 0;
}

