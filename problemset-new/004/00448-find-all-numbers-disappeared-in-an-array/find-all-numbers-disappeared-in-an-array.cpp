/*************************************************************************
  > File Name: find-all-numbers-disappeared-in-an-array.cpp
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
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        
        #define GET_VALUE(pos) nums[pos - 1]
        #define SET_VALUE(pos, value) nums[pos - 1] = value
        
        vector<int> ans;
        int nowPos = 0, realPos = 0;
        
        //由于最多有N个数字, while循环累计执行N次, for循环也执行N次,总共执行2N次
        for(nowPos = 1; nowPos <= nums.size(); nowPos++){
            while(GET_VALUE(nowPos) != nowPos && GET_VALUE(nowPos) != 0){
                realPos = GET_VALUE(nowPos);
                
                //找到一对相等的
                if(GET_VALUE(realPos) == GET_VALUE(nowPos)){
                    SET_VALUE(realPos, 0);
                }else{
                    std::swap(GET_VALUE(nowPos), GET_VALUE(realPos));
                }
            }
        }
        
        for(nowPos = 1; nowPos <= nums.size(); nowPos++){
            if(GET_VALUE(nowPos) != nowPos){
                ans.push_back(nowPos);
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
    vector<int> ans;
    ans = work.findDisappearedNumbers(nums);
    
    output("nums", nums);
    output("ans", ans);
}

int main() {
    vector<int> nums;

    nums = {4,3,2,7,8,2,3,1};
    test(nums);


    return 0;
}
