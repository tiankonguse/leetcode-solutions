/*************************************************************************
    > File Name: available-captures-for-rook.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年02月27日 21:28:32
 ************************************************************************/

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<time.h>
#include "../../include/base.h"
using namespace std;


#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;



class Solution {

public:
    int numRookCaptures(vector<vector<char>>& board) {
        int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int rookx = 0, rooky = 0;
        for(int i=0; i<8; i++) {
            for(int j=0; j<8; j++) {
                if(board[i][j] == 'R') {
                    rookx = i;
                    rooky = j;
                }
            }
        }
        //printf("xy: %d %d\n", rookx, rooky);
        int ans = 0;
        int tmpx, tmpy;
        for(int i=0; i<4; i++) {
            tmpx = rookx;
            tmpy = rooky;
            //printf("dir: %d %d\n", dir[i][0], dir[i][1]);
            while(tmpx >=0 && tmpx < 8 && tmpy >=0 && tmpy < 8) {
                //printf("pos: %d %d\n", tmpx, tmpy);
                if(board[tmpx][tmpy] == 'B') {
                    break;
                }
                if(board[tmpx][tmpy] == 'p') {
                    ans++;
                    break;
                }
                tmpx = tmpx + dir[i][0];
                tmpy = tmpy+ dir[i][1];
            }
        }
        return ans;
    }
};

void test(vector<vector<char>>& data) {
    Solution work;
    int ans;
    ans = work.numRookCaptures(data);
    output("data", data);
    output("ans", ans);
}

int main() {
    vector<vector<char> > data;

    data = {{'.','.','.','.','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'.','.','.','R','.','.','.','p'},{'.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.'}};
    test(data);

    data = {{'.','.','.','.','.','.','.','.'},{'.','p','p','p','p','p','.','.'},{'.','p','p','B','p','p','.','.'},{'.','p','B','R','B','p','.','.'},{'.','p','p','B','p','p','.','.'},{'.','p','p','p','p','p','.','.'},{'.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.'}};
    test(data);

    data = {{'.','.','.','.','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'p','p','.','R','.','p','B','.'},{'.','.','.','.','.','.','.','.'},{'.','.','.','B','.','.','.','.'},{'.','.','.','p','.','.','.','.'},{'.','.','.','.','.','.','.','.'}};
    test( data);

    return 0;
}
