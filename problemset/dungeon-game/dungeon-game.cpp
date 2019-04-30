/*************************************************************************
    > File Name: dungeon-game.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月19日 星期日 13时34分33秒
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
    vector<vector<int> >ans;
    void init(vector<vector<int> >&board){
        int n = board.size();
        int m = board[0].size();
        ans.resize(n);
        
        for(int i=0;i<n;i++){
            ans[i].resize(m);
        }
    }

    bool check(vector<vector<int> >&board){
        int n = board.size();
        int m = board[0].size();
        ans[0][0] = board[0][0];

        if(ans[0][0] <= 0){
            return false;
        }
        if(debug){
            printf("(0,0) = %d\n", ans[0][0]);
        }

        for(int i=1;i<n;i++){
            if(ans[i-1][0] <= 0){
                ans[i][0] = -1;
            }else{
                ans[i][0] = ans[i-1][0] + board[i][0];
            }
            if(debug){
                printf("(%d,0) = %d\n", i, ans[i][0]);
            }
        }
        for(int i=1;i<m;i++){
            if(ans[0][i-1] <= 0){
                ans[0][i] = -1;
            }else{
                ans[0][i] = ans[0][i-1] + board[0][i];
            }
            if(debug){
                printf("(%d,%d) = %d\n", 0, i, ans[0][i]);
            }
        }

        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                if(ans[i-1][j] <=0 && ans[i][j-1] <= 0){
                    //both < 0
                    ans[i][j] = -1;
                }else if(ans[i-1][j] <=0 && ans[i][j-1] > 0){
                    //up > 0, left < 0
                    ans[i][j] = ans[i][j-1] + board[i][j];
                }else if(ans[i-1][j] > 0 && ans[i][j-1] <= 0){
                    //left >0 , up < 0
                    ans[i][j] = ans[i-1][j] + board[i][j];
                }else{
                    //both > 0
                    ans[i][j] = max(ans[i-1][j], ans[i][j-1]) + board[i][j];
                }
                if(debug){
                    printf("(%d,%d) = %d\n", i, j, ans[i][j]);
                }
            }
        }
        
        if(ans[n-1][m-1] <= 0){
            return false;
        }else{
            return true;
        }
    }

    int max(int a, int b){
        if(a<b){
            return b;
        }else{
            return a;
        }
    }

    int getMax(vector<vector<int> >& board){
        int n = board.size();
        int m = board[0].size();
        int ans = 1;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans += abs(board[i][j]);
            }
        }
        return ans;
    }

    int abs(int a){
        if(a<0){
            return -a;
        }else{
            return a;
        }
    }
    int debug;
public:
    Solution(int debug=0):debug(debug){

    }
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        init(dungeon);

        int left = 1;
        int right = getMax(dungeon);
        int mid;

        if(debug){
            printf("left=%d right=%d\n", left, right);
        }

        while(left < right){
            mid = (left + right)/2;
            if(debug){
                printf("l=%d r=%d m=%d\n", left, right, mid);
            }
            dungeon[0][0] += mid;
            if(check(dungeon)){
                if(debug){
                    printf("mid=%d true\n", mid);
                }
                right = mid;
            }else{
                if(debug){
                    printf("mid=%d false\n", mid);
                }
                left = mid + 1;
            }
            dungeon[0][0] -= mid;
        }
        return left;
    }
};


void output(vector<vector<int> >& board){
    int n= board.size();
    for(int i=0;i<n;i++){
        int m = board[i].size();
        for(int j=0;j<m;j++){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void test(int debug=0){
    srand(time(NULL));
    Solution work(debug);

    vector<vector<int> >data;
    int ans;

    data = {
        {-2, -3, 3},
        {-5, -10, 1},
        {10, 30, -5}
    };
    output(data);
    ans = work.calculateMinimumHP(data);
    printf("ans=%d\n\n", ans);

}

int main(int argc, char** argv){
    int debug = 0;
    if(argc == 2){
        debug = atoi(argv[1]);
        printf("argc=%d debug=%d\n", argc,debug);
        for(int i=0;i<argc;i++){
            printf("%s\n",argv[i]);
        }
    }
    test(debug);
    return 0;
}
