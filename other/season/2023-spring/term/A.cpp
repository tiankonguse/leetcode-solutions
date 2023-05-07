// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
public:
    int runeReserve(vector<int>& a) {
        std::sort(a.begin(),a.end());
        int ans = 1;
        int now = 1;
        int n = a.size();
        for(int i = 1; i < n; i ++ ) {
            if (abs(a[i]-a[i-1]) <= 1) {
                now ++ ;
                if (now > ans) ans = now;
            } else {
                now  = 1;
            }
        }
        return ans;
    }
};
