/*************************************************************************
    > File Name: unique-paths.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月22日 星期三 01时23分09秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int> >board(m, vector<int>(n));
        if(m<=0 || n<=0){
            return 0;
        }

        board[0][0] = 1;
        for(int i=0;i<m;i++){
            for(int j=0; j<n;j++){
                if(i == 0 || j == 0){
                    board[i][j] = 1;
                }else{
                    board[i][j] = board[i-1][j] + board[i][j-1];
                }
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
        
        return board[m-1][n-1];
    }
};

void test(){
    srand(time(NULL));
    Solution work;

    int m,n;
    int ans;

    m = 0;
    n = 0;
    ans = work.uniquePaths(m,n);
    printf("m=%d n=%d ans=%d\n", m, n, ans);
    
    m = 1;
    n = 1;
    ans = work.uniquePaths(m,n);
    printf("m=%d n=%d ans=%d\n", m, n, ans);
    
    m = 1;
    n = 9;
    ans = work.uniquePaths(m,n);
    printf("m=%d n=%d ans=%d\n", m, n, ans);
    
    m = 3;
    n = 4;
    ans = work.uniquePaths(m,n);
    printf("m=%d n=%d ans=%d\n", m, n, ans);
    
    m = 10;
    n = 10;
    ans = work.uniquePaths(m,n);
    printf("m=%d n=%d ans=%d\n", m, n, ans);
}

int main(){
    test();
    return 0;
}
