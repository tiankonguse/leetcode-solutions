/*************************************************************************
  > File Name: remove-element.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年05月21日 星期四 22时33分16秒
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
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
    int removeElement(vector<int>& nums, int val) {
        int ans = nums.size();
        for(int i=0;i<nums.size();i++){
            if(nums[i] == val){
                ans = ans - 1;
            }
        }
        return ans;
    }
};

int main() {
    vector<int>nums;
    int val;
    int ans;
    Solution work;

    nums = {1,2,3,4,2};
    val = 2;
    ans = work.removeElement(nums, val);
    printf("nums=1,2,3,4,2 val=%d ans=%d\n",val, ans);

    nums = {1,2,3,4,2};
    val = 4;
    ans = work.removeElement(nums, val);
    printf("nums=1,2,3,4,2 val=%d ans=%d\n",val, ans);

    nums = {1,2,3,4,2};
    val = 3;
    ans = work.removeElement(nums, val);
    printf("nums=1,2,3,4,2 val=%d ans=%d\n",val, ans);

    nums = {4,5};
    val = 4;
    ans = work.removeElement(nums, val);
    printf("nums=4,5 val=%d ans=%d\n",val, ans);

    return 0;
}
