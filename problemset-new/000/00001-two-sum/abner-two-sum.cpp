/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map <int, int> map;
        vector<int> result;
        int size = nums.size();
        for(int i = 0; i < size; ++i) {
            auto it = map.find(target - nums[i]);
            if(it != map.end()){
                result.push_back(it->second);
                result.push_back(i);
                break;
            }
            map[nums[i]] = i;
        }

        return result;
    }
};

