/*************************************************************************
  > File Name: permutations.cpp
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
    
    void init(){
        n = 0;
        ans.clear();
        output.clear();
        use.clear();
    }
    
    void dfs(int lev, vector<int>& nums){
        if(lev == n){
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

    vector<vector<int>> permute(vector<int>& nums) {
        init();
        n = nums.size();
        for(int i=0;i<n;i++){
            use.push_back(1);
        }
        
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
    ans = work.permute(nums);
    output("ans", ans);
}

int main() {
    vector<int> nums;

    nums = {1,2,3,4};
    test(nums);


    return 0;
}
