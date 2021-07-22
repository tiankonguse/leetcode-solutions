#include "base.h"

class Solution {
 public:
  int findRepeatNumber(vector<int>& nums) {
    int n = nums.size();
    for(int i=0;i<nums.size();i++){
        while(i != nums[i]) {
            int j = nums[i];
            if(nums[i] == nums[j]) return nums[i];
            swap(nums[i], nums[j]);
        }
    }

    return 0;
  }
};

int main() {
  TEST_SMP1(Solution, findRepeatNumber, 2, vector<int>({2, 3, 1, 0, 2, 5, 3}));

  return 0;
}