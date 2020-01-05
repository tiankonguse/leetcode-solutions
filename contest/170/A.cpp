class Solution {
public:
    string freqAlphabets(string s) {
        string ans;
        for(int i = 0; i < s.length(); i++){
            if(i + 2 < s.length() && s[i + 2] == '#'){
                int base = (s[i] - '0') * 10 + s[i+1] - '0';
                ans.push_back(base - 10 + 'j');
                i += 2;
            }else{
                ans.push_back(s[i] - '1' + 'a');
            }
        }
        return ans;
    }
};
