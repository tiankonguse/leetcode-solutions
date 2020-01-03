class Solution {
    string s, p;
    map<pair<int,int>, bool> hash;
    bool check(int _l, int _r){
        int l = _l, r = _r;
        if(hash.count({_l, _r}) > 0) return false; //dp cache
        
        if(l == s.length() && r == p.length()) return true; //one
        if(l != s.length() && r == p.length()) return hash[{_l, _r}] = false; //tow
        
        if(l == s.length() && r != p.length()){ //three
            while(r < p.length() && p[r] == '*'){
                r++;
            }
            return hash[{_l, _r}] =  r == p.length();
        }
        
        if(s[l] == p[r] || p[r] == '?') return hash[{_l, _r}] = check(l + 1, r + 1); //four
        if(p[r] != '*') return hash[{_l, _r}] = false; //five
        
             
        //last is *, eq
        if(r + 1 == p.length()){ //six
            return true;
        }
        
        while(l < s.length()){ //seven
            if(check(l, r+1)){
                return true;
            }
            l++;
        }
        return hash[{_l, _r}] = false;
    }
public:
    bool isMatch(string _s, string _p) {
        s = _s, p = _p;
        return check(0, 0);
    }
};


