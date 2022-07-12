#include "base.h"

class Solution {
public:
    int minDeletions(string s) {
        map<char, int> charToNum;
        for(auto c: s){
            charToNum[c]++;
        }
        
        map<int, int> numToGroup;
        for(auto p: charToNum){
            numToGroup[p.second]++;
        }
        
        
        int ans = 0;
        
        while(numToGroup.size() > 0){
            auto it = numToGroup.end();
            it--;
            
            int n = it->first;
            int m = it->second;
            numToGroup.erase(it);
            ans += m - 1;
            
            if(m > 1 && n > 1){
                numToGroup[n-1] += m - 1;
            }
            
        }
        
        return ans;
    }
};

int main() {
    TEST_SMP1(Solution, minDeletions, 0, "aaa");
    TEST_SMP1(Solution, minDeletions, 2, "aaabbbcc");
    TEST_SMP1(Solution, minDeletions, 2, "ceabaacb");

    return 0;
}
