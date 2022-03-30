/*************************************************************************
  > File Name: search-insert-position.cpp
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
    int searchInsert(vector<int>& nums, int target) {
        int ans = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]> target){
                return ans;
            }else if(nums[i] == target){
                return i;
            }else{
                ans = i + 1;
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


void test(vector<int>& nums, int target){
    Solution work;
    int ans;
    ans = work.searchInsert(nums, target);
    
    output("nums", nums);
    output("target", target);
    output("ans", ans);
}

int main() {
    vector<int> nums;
    int target;

    nums = {1,3,5,6};
    target = 5;
    test(nums, target);

    nums = {1,3,5,6};
    target = 2;
    test(nums, target);


    nums = {1,3,5,6};
    target = 7;
    test(nums, target);


    nums = {1,3,5,6};
    target = 0;
    test(nums, target);

    return 0;
}
