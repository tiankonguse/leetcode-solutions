#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int arrangeCoins(int n) {
        int lo = 0, hi = 1<<16;
        while(lo < hi) {
            int mid = lo+(hi-lo)/2;
            int temp = 1LL*mid * ((mid+1)/2) + (mid%2 ? 0 : mid/2);
            if(temp < n) lo = mid+1;
            else hi = mid;
        }
        if(1LL*lo*((lo+1)/2)+(lo%2?0:lo/2) == n) return lo;
        else return lo-1;
    }
};
int main()
{
    return 0;
}
