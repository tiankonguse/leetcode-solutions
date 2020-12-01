class Solution {
    vector<int> base;
    void born(vector<string>& words){
        for(auto& s: words){
            set<char> tmp;
            int bit = 0;
            for(auto c:s){
                tmp.insert(c);
                bit = bit | (1<<(c-'a'));
            }
            if(tmp.size() >7)continue;
            base.push_back(bit);
        }
    }
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        vector<int> ans;
        born(words);
        
        for(auto& s: puzzles){
            int num = 0;
            int bit = 0;
            for(auto c: s){
                bit = bit | (1<<(c-'a'));
            }
            int firstBit = 1 << (s[0] - 'a');
            for(auto v: base){
                if((v & bit) == v && ((firstBit & v) == firstBit)){
                    num++;
                }
            }
            ans.push_back(num);
        }
        
        return ans;
    }
};
