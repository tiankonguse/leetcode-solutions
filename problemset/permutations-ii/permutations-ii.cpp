/*************************************************************************
  > File Name: permutations-ii.cpp
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
	vector<vector<int>> ans;
    vector<int> output;
    vector<int> use;
    int n;
    int maxLev;
    
    void init(vector<int>& nums){
        ans.clear();
        output.clear();
        use.clear();
        
        vector<int> newNums;
        map<int, int> m;
        
        maxLev = nums.size();
        
        for(int i=0;i<nums.size();i++){
            if(m.find(nums[i]) == m.end()){
                newNums.push_back(nums[i]);
                use.push_back(1);
                m[nums[i]] = newNums.size() - 1;
            }else{
                use[m[nums[i]]]++;
            }
        }
        nums = newNums;
        n = nums.size();
    }
    
    void dfs(int lev, vector<int>& nums){
        if(lev == maxLev){
            ans.push_back(output);
            return ;
        }
        for(int i=0; i< n;i++){
            if(use[i]){
                use[i]--;
                output.push_back(nums[i]);
                dfs(lev +1, nums);
                output.pop_back();
                use[i]++;
            }
        }
    }
    
public:

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        init(nums);
        
        dfs(0, nums);
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
    vector<vector<int>> ans;
    output("nums", nums);
    ans = work.permuteUnique(nums);
    output("ans", ans);
}

int main() {
    vector<int> nums;

    nums = {1,1,2};
    test(nums);


    return 0;
}
