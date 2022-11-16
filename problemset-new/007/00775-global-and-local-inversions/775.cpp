#include <bits/stdc++.h>

#include "base.h"
using namespace std;


class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        int n = nums.size();
        
        for(int i=0;i<n;i++){
            if(i == nums[i]) continue;

            if(i + 1 != nums[i]) return false;
            if(nums[i+1] != i) return false;
            i++;
        }
        return true;

    }
};
