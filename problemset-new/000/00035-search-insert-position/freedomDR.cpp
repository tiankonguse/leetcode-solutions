#include <bits/stdc++.h>

using namespace std;

/*
 * 每天写写二分查找，左闭右开标准，锻炼手部肌肉
 */
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size();
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            if(nums[mid] < target) lo = mid+1;
            else hi = mid;
        }
        return lo;
    }
};

int main()
{
    return 0;
}
