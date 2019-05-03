/*************************************************************************
    > File Name: two-sum.cpp
    > Author: ctimbai 
    > Created Time: 2015年04月12日 星期日 02时09分42秒
 ************************************************************************/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        if (nums.size() <= 1) {
            return vector<int>();
        }
        
        vector<int> res;
        
        unordered_map<int, int> nummap;
        for (int i = 0; i < nums.size(); i ++) {
            nummap[nums[i]] = i;
        }
        
        for (int i = 0; i < nums.size(); i ++) {
            int search = target - nums[i];
            if (nummap.find(search) != nummap.end() && nummap[search] != i) {
                res.push_back(i);
                res.push_back(nummap[search]);
                break;
            }
        }
        return res;
    }
};