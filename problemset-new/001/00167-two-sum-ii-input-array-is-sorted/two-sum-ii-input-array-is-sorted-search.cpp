/*************************************************************************
    > File Name: two-sum-ii-input-array-is-sorted-search.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Mar 14 23:38:45 2019
 ************************************************************************/

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<time.h>
#include "../../include/base.h"
using namespace std;


#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;
auto __ =[]() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}
();

class Solution {
    int findRight(vector<int>& numbers, int target, int left) {
        int leftVal = numbers[left];
        left = left + 1;
        int right = numbers.size() - 1;
        int mid = 0;

        while(left <= right){
            mid = (left + right)/2;
            if(numbers[mid] + leftVal == target){
                return mid;
            }else if(numbers[mid] + leftVal < target){
                left = mid + 1;
            }else if(numbers[mid] + leftVal > target){
                right = mid - 1;
            }
        }
        return -1;
    }
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ans;
        for(int left=0; left<numbers.size(); left++) {
            int right = this->findRight(numbers, target, left);
            if(right != -1) {
                ans.push_back(left+1);
                ans.push_back(right+1);
                return ans;
            }
        }
        return ans;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.twoSum(firstData, secondData);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("firstData", firstData);
        output("secondData", secondData);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    vector<int> first;
    int second;
    vector<int> expectAns;


    first = {2,7,11,15};
    second = 9;
    expectAns = {1,2};
    test(expectAns, first, second);


    first = {2,7,11,15};
    second = 13;
    expectAns = {1,3};
    test(expectAns, first, second);


    first = {2,7,11,15};
    second = 17;
    expectAns = {1,4};
    test(expectAns, first, second);

    return 0;
}

