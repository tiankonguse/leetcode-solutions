
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        int n = nums.size();
        string ans;
        if(n == 1){
            ans.append(to_string(nums[0]));
        }else         if(n == 2){
            ans.append(to_string(nums[0]));
            ans.push_back('/');
            ans.append(to_string(nums[1]));
        }else{
            ans.append(to_string(nums[0]));
            ans.push_back('/');
            ans.push_back('(');
            ans.append(to_string(nums[1]));
            for(int i=2;i<n;i++){
            ans.push_back('/');
            ans.append(to_string(nums[i]));
            }
            ans.push_back(')');
        }
        return ans;
    }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& nums, const string& ans) {
  TEST_SMP1(Solution, optimalDivision, ans, nums);
}

int main() {
  Test({1000,100,10,2}, "1000/(100/10/2)");
  Test({2,3,4}, "2/(3/4)");
  return 0;
}

#endif