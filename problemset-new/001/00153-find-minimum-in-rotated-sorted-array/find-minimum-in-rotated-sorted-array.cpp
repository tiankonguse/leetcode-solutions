/*************************************************************************
  > File Name: find-minimum-in-rotated-sorted-array.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 13:50 2017/8/23
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

class Solution {
public:
    int findMin(vector<int>& nums) {
        int ans = nums[0];
        for(int i=0;i<nums.size();i++){
            if(nums[i] < ans){
                ans = nums[i];
            }
        }
        return ans;
    }
};

void output(char const* name, std::string &data){
    printf("%s:\n   %s\n", name, data.c_str());
    printf("\n");
}

void output(char const* name, int data){
    printf("%s:\n    %d\n", name, data);
    printf("\n");
}

void output(char const* name, vector<int>&data){
    printf("%s:", name);
    for(int i=0;i<data.size();i++){
        printf("%d ", data[i]);
    }
    printf("\n");
}

void output(char const* name, vector<vector<int>>&data){
    printf("%s:\n", name);
    for(int i=0;i<data.size();i++){
        output("    ", data[i]);
    }
    printf("\n");
}


void test(vector<int>& nums){
    Solution work;
    int ans;
    ans = work.findMin(nums);
    
    output("nums", nums);
    output("ans", ans);
}

int main() {
    vector<int> nums;

    nums = {4,5,6,7,0,1,2};
    test(nums);


    return 0;
}
