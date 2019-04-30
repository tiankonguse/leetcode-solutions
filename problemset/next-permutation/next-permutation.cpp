/*************************************************************************
  > File Name: next-permutation.cpp
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
	bool isNotPossible(vector<int>& nums, int start, int end){
		for(int i = start; i< end; i++){
			if(nums[i] < nums[i+1]){
				return false;
			}
		}
		return true;
	}
	
	void rearrange(vector<int>& nums, int start, int end){
		while(start < end){
			std::swap(nums[start], nums[end]);
			start++, end--;
		}
	}
	
	int findFirstAscendPos(vector<int>& nums, int end){
		while(nums[end] <= nums[end-1]){
			end--;
		}
		return end - 1;
	}
	
	int findFirstBigAscendPos(vector<int>& nums, int start, int end){
		while(nums[start] >= nums[end]){
			end--;
		}
		return end;
	}
	
public:



    void nextPermutation(vector<int>& nums) {
        if(isNotPossible(nums, 0, nums.size()-1)){
			rearrange(nums, 0, nums.size()-1);
			return ;
		}
		
		//肯定有答案，需要先找到第一个降低的位置
		int firstAscendPos = findFirstAscendPos(nums, nums.size()-1);
		
		//找到大于且最接近pos的位置
		int firstBigAscendPos = findFirstBigAscendPos(nums, firstAscendPos, nums.size()-1);
		std::swap(nums[firstAscendPos], nums[firstBigAscendPos]);
		rearrange(nums, firstAscendPos + 1, nums.size()-1);
		
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
    output("nums", nums);
    work.nextPermutation(nums);
    output("ans", nums);
}

int main() {
    vector<int> nums;

    nums = {1,2,3};
    test(nums);

    nums = {3,2,1};
    test(nums);

    nums = {1,1,5};
    test(nums);

    return 0;
}
