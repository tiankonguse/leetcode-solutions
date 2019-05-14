#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int mod = 1e7+7;
    int check(string S, int len) {
        map<int, set<int>> s;
        int base = 1, value = 0;
        for(int i = 0; i < len; ++i) {
            value = value*26 + (S[i]-'a');
            value %= mod;
            base *= 26;
            base %= mod;
        }
        s[value].insert(0);
        for(int i = len; i < S.size(); i++) {
            value = value*26 + (S[i]-'a') - (S[i-len]-'a')*base;
            while(value < 0) value += mod; //防止负数
            value = value%mod;
            if(!s[value].empty()) {
                string s2 = S.substr(i-len+1, len);
                for(int st : s[value]) {
                    string s1 = S.substr(st, len);
                    if(s1 == s2){ 
                        return i-len+1;
                    }
                }
            }
            s[value].insert(i-len+1);
        }
        return -1;
    }
    string longestDupSubstring(string S) {
        int len = 0, st = 0;
        int lo = 1, hi = S.size();
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            int res = check(S, mid);
            if(res != -1) {
                st = res;
                len = mid;
                lo = mid+1;
            }else {
                hi = mid;
            }
        }
        return S.substr(st, len);
    }
};

int main()
{
    return 0;
}
