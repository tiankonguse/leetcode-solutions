/*************************************************************************
    > File Name: unique-binary-search-trees.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月06日 星期一 14时32分30秒
 ************************************************************************/

#include<stdio.h>
#include<map>
using namespace std;

class Solution {
    map<int, int>m;
public:

    Solution(){
        m[0] = 1;
        m[1] = 1;
    }

    int numTrees(int n) {
        if(m.find(n) == m.end()){
            int ans = 0;
            for(int i=0;i<n;i++){
                ans += numTrees(i) * numTrees(n-1-i);
            }
            m[n] = ans;
        }
        return m[n]; 
    }
};


void test(){
    Solution work;
    printf("%d\n",work.numTrees(3));
    printf("%d\n",work.numTrees(4));
    printf("%d\n",work.numTrees(7));
}

int main(){
    test();
    return 0;
}
