#include <bits/stdc++.h>

using namespace std;
/*
 * 注意int越界
 */
class Solution {
public:
    int mySqrt(int x) {
        int lo = 1, hi = x;
        while(lo < hi) {
            int mid = lo+(hi-lo)/2;
            if(1LL*mid*mid < 1LL*x) lo = mid + 1;
            else hi = mid;
        }
        if(1LL*lo*lo == 1LL*x) return lo;
        else return lo-1;
    }
};

int main()
{
    return 0;
}
