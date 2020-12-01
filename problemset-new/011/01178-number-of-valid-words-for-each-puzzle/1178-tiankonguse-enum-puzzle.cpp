class Solution {
    map<int, int> base;
    void born(vector<string>& words){
        for(auto& s: words){
            int bit = 0;
            for(auto c:s){
                bit |= 1<<(c-'a');
            }
            ++base[bit];
        }
    }
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        vector<int> ans;
        born(words);
        
        for(auto& s: puzzles){
            int num = 0;
            int len = s.length() - 1;
            for(int i = 0; i < (1 << len); i++){
                int mask = 1 << (s[0] - 'a');
                for(int j=0;j<len;j++){
                    if(i & (1<<j)){
                        mask |= 1 << (s[j+1] - 'a');
                    }
                }
                if(base.count(mask) > 0){
                    num += base[mask];
                }
                
            }
            ans.push_back(num);
        }
        
        return ans;
    }
};
