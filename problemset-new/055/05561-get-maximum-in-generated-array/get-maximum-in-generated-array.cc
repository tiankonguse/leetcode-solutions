#include "base.h"

class Solution {
public:
    // nums[2 * i] = nums[i]
    // nums[2 * i + 1] = nums[i] + nums[i + 1]
    int getMaximumGenerated(int n) {
        if(n == 0) return 0;
        int ans = 1;
        vector<int> str;
        str.push_back(0);
        str.push_back(1);
        for(int i = 2; i<= n;i++){
            int tmp = 0;
            if(i % 2 == 0){
                tmp = str[i/2];
            }else{
                tmp = str[i/2] + str[i/2+1];
            }
            str.push_back(tmp);
            ans = max(ans, tmp);
        }
        return ans;
    }
};

int main() {
    TEST_SMP1(Solution, getMaximumGenerated, 3, 7);
    TEST_SMP1(Solution, getMaximumGenerated, 1, 2);
    TEST_SMP1(Solution, getMaximumGenerated, 2, 3);

    return 0;
}
