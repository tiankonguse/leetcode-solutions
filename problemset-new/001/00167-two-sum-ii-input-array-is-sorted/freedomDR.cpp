#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int len = numbers.size();
        for(int i = 0; i < len-1; i++) {
            int lo = i+1, hi = len, t = target-numbers[i];
            while( lo < hi ){
                int mid = lo+(hi-lo)/2;
                if(numbers[mid] < t) lo = mid+1;
                else hi = mid;
            }
            if(lo != len && numbers[lo] == t) return {i+1, lo+1};
        }
        return {};
    }
};
int main()
{
    return 0;
}
