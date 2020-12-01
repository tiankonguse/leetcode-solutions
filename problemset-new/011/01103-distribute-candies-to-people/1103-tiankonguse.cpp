/*************************************************************************
    > File Name: distribute-candies-to-people.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2019年06月30日 11:37:47
    > link:
    > No: 1103. Distribute Candies to People
    > Contest: https://leetcode.com/contest/weekly-contest-143
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    vector<int> distributeCandies(int _sum, int n) {
        vector<int> ans(n, 0);
        long long sum = _sum;
        int num = (sqrt(1.0 + 8 * sum) - 1)/2;
        long long k = num/n;
        //printf("num=%d k=%lld\n", num, k);
        
        int minAns = k * (k-1) / 2 * n;
        for(int i=0;i<n;i++){
            ans[i] = minAns + (i+1)*k;
            sum -= ans[i];
        }
        int start = k*n+1;
        for(int i=0;sum > 0;i++, start++){
            if(start <= sum){
                ans[i] += start;
            }else{
                ans[i] += sum;
            }
            sum -= start;
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
