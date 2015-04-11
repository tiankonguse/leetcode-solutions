/*************************************************************************
    > File Name: single-number.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年03月31日 星期二 23时35分19秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Solution {

public:

    int singleNumber(int A[], int n) {
        int ans = 0;
        
        for(int i=0;i<n;i++){
            ans ^= A[i];
        }

        return ans;              

    }

};

int main(){
    return 0;
}

