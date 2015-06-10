/*************************************************************************
  > File Name: remove-duplicates-from-sorted-array.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年06月11日 星期四 00时34分49秒
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
    int removeDuplicates(vector<int>& nums) {
        int s = nums.size();
        if(s == 0){
            return 0;
        }
        int l=1, r=1;


        for(;r < s;){
            if(nums[r] != nums[l-1]){
                nums[l++] = nums[r];
            }
            r++;
        }
        return l;
    }
};
int main() {

    return 0;
}
