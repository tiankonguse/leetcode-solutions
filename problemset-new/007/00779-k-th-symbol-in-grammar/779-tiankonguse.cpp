/*************************************************************************
    > File Name: 779-tiankonguse.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: Sun Jun 16 22:10:52 2019
 ************************************************************************/

class Solution {
public:
    int kthGrammar(int N, int K) {
        if(N == 1 || K == 0) return 0;
        if(kthGrammar(N-1, (K+1)/2)){
            return K%2;
        }else{
            return 1 - K%2;
        }
    }
};


