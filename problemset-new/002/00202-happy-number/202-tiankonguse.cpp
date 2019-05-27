/*************************************************************************
    > File Name: 202-tiankonguse.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon May 27 22:56:18 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
   int happy(int n){
        int ans = 0;
        while(n){
            ans += (n % 10) * (n % 10);
            n = n / 10;
        }
        return ans;
    }
public:
    bool isHappy(int n) {
        set<int> s;
        while(s.find(n) == s.end()){
            s.insert(n);
            n = happy(n);
            if(n == 1){
                return true;
            }
        }
        return false;
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
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
