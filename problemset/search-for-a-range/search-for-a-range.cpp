/*************************************************************************
  > File Name: search-for-a-range.cpp
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
    int binaryLowBound(vector<int>& nums, int target){
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        
        if(nums.size() == 0){
            return -1;
        }
        
        
        while(left < right){
            mid = (left + right)/2;
            
            if(nums[mid] < target){
                left = mid + 1;
            }else{
                right = mid;
            }
        }
        
        if(nums[left] == target){
            return left;
        }else{
            return -1;
        }
    }
    
    int binaryUpBound(vector<int>& nums, int target){
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        
        if(nums.size() == 0){
            return -1;
        }
        
        while(left < right){
            mid = (left + right + 1)/2;
            if(nums[mid] > target){
                right = mid - 1;
            }else{
                left = mid;
            }
        }
        
        if(nums[left] == target){
            return left;
        }else{
            return -1;
        }
        
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans;
        ans.push_back(binaryLowBound(nums, target));
        ans.push_back(binaryUpBound(nums, target));
        return ans;
    }
};

void output(char const* name, std::string &data){
    printf("%s:\n   %s\n", name, data.c_str());
}

void output(char const* name, int data){
    printf("%s:\n    %d\n", name, data);
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
    vector<int> ans;
    output("nums", nums);
    output("target", target);
    ans = work.searchRange(nums, target);
    output("ans", ans);
}

int main() {
    vector<int> nums;

    nums = {5, 7, 7, 8, 8, 10};
    test(nums, 8);
    
    nums = {5, 7, 7, 8, 8, 8, 10};
    test(nums, 8);

    nums = {5, 7, 7, 8, 8, 8, 8, 10};
    test(nums, 8);

    
    nums = {5, 7, 7, 8, 8, 10};
    test(nums, 9);
    
    
    nums = {5, 7, 7, 8, 8, 10};
    test(nums, 11);
    
    
    nums = {5, 7, 7, 8, 8, 10};
    test(nums, 4);
    
    return 0;
}
