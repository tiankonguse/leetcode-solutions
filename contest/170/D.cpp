class Solution {
    map<pair<int, int>, int> m;
    string s;
    int dp(int l, int r){
        auto p = pair(l, r);
        if(m.count(p)) return m[p];
        if( l > r) return m[p] = 0;
        
        if(l == r) return m[p] = 1;
        
        if(s[l] == s[r]){
            return m[p] = dp(l+1, r-1) + 2;
        }
        
        return m[p] = max(dp(l+1, r), dp(l, r-1));
    }
public:
    int minInsertions(string _s) {
        s = _s;
        int maxAns = dp(0, s.length() - 1);
        return s.length() - maxAns;
        
    }
};


