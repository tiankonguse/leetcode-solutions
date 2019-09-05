class Solution {
    vector<map<char, int>> base;
    void born(string&s){
        map<char,int> m;
        base.push_back(m);
        for(auto c: s){
            m[c]++;
            base.push_back(m);
        }
    }
    
    int getRange(int l, int r){
        int ans = 0;
        map<char, int> tmp = base[r+1];
        for(auto&p : base[l]){
            tmp[p.first] -= p.second;
        }
        for(auto&p: tmp){
            if(p.second %2 == 1)ans++;
        }
        return ans;
    }
public:
    vector<bool> canMakePaliQueries(string& s, vector<vector<int>>& queries) {
        born(s);
        vector<bool>ans;
        
        for(auto& q: queries){
            int num = getRange(q[0], q[1]);
            if(num/2 <= q[2]){
                ans.push_back(true);
            }else{
                ans.push_back(false);
            }
        }
        
        return ans;
    }
};
