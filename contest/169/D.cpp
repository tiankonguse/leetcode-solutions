class Solution {
    vector<string> words;
    string result;
    map<char, int> m;
    vector<char> vec;
    vector<int> val;
    vector<int> use; //num is use
    vector<int> index;
    
    int getVal(string& str, int defaultVal = -1, int start = 100){
        int sum = 0;
        
        int base = 1;
        for(int i = str.length() - 1, j = 0; i >= 0 && j < start; i--, j++){
            int v = val[m[str[i]]];
            if(v == -1){
                v = defaultVal;
            }
            sum += v * base;
            base *= 10;
        }
        return sum;
    }
    
    bool check(){
        int resultVal = getVal(result);
        int sum = 0;
        for(auto& s: words){
            sum += getVal(s);
            if(sum > resultVal){
                return false;
            }
        }
        return sum == resultVal;
    }
    
    bool checkNoPreZero(string& str){
        if(str.size() == 1){
            return true;
        }
        return val[m[str[0]]] != 0;
    }
    bool checkNoPreZero(){
        if(!checkNoPreZero(result)){
            return false;
        }
        for(auto& s: words){
            if(!checkNoPreZero(s)){
                return false;
            }
        }
        return true;
    }
    
    bool less(){
        int resultVal = getVal(result, 9);
        int sum = 0;
        for(auto& s: words){
            sum += getVal(s, 0);
            if(sum > resultVal){
                return false;
            }
        }
        return true;
    }
    bool eq(int start){
        if(start == 0){
            return true;
        }
        int resultVal = getVal(result, 9, start);
        int sum = 0;
        for(auto& s: words){
            sum += getVal(s, 0, start);
        }
        
        
        int base = 1;
        for(int i=0;i<start;i++){
            base *= 10;
        }
        
        return sum%base == resultVal%base;
    }
    
    bool dfs(int pos){
        if(pos == vec.size()){
            return check();
        }
        for(int i=0;i<10;i++){
            if(use[i]) continue;
            use[i] = 1;
            val[pos] = i;
            if(checkNoPreZero() && eq(index[pos]-1) && dfs(pos + 1)){
                return true;
            }
            val[pos] = -1;
            use[i] = 0;
        }
        return false;
    }
    
    void add(string& result){
        for(auto c: result){
            if(m.count(c) == 0){
                m[c] = vec.size();
                vec.push_back(c);
            }
        }
    }
    void init(){
        vector<string> tmpList;
        tmpList = words;
        tmpList.push_back(result);
        for(auto& s: tmpList){
            reverse(s.begin(), s.end());
        }
        
        sort(tmpList.begin(), tmpList.end(), [](auto& a, auto& b){
            if(a.length() != b.length()){
                return a.length() > b.length();
            }
            return a < b;
        });
        
        // for(auto& v: tmpList){
        //     printf("s: %s\n", v.c_str());
        // }
        
        int maxLen = tmpList[0].length();
        for(int i = 1; i <= maxLen; i++){
            for(auto& s: tmpList){
                if(s.length() < i){
                    break;
                }
                char c = s[i-1];
                if(m.count(c) == 0){
                    m[c] = vec.size();
                    vec.push_back(c);
                    index.push_back(i);
                    //printf("c:%c %d\n", c, index.back());
                }
            }
        }
        
        use.resize(10, 0);
        val.resize(vec.size(), -1);
    }
public:
    bool isSolvable(vector<string>& words, string result) {
        this->words = words;
        this->result = result;
        init();
        return dfs(0);
    }
};
