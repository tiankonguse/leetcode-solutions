/*************************************************************************
  > File Name: word-search.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月23日  9:03:04
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

class Solution {
    int x;
    int y;
    string word;
    int m[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    vector<vector<int> >have;
    void init(){
        have.resize(x);
        for(int i=0;i<x;i++){
            have[i].resize(y);
        }
    }
    void reset(){
        for(int i=0;i<x;i++){
            fill(have[i].begin(), have[i].end(), 0);
        }
    }

    bool check(int i, int j, int lev, vector<vector<char> >&board){
        if(lev == word.size()){
            return true;
        }
        if(i<0 || j<0 || i >= x || j >= y){
            return false;
        }        
        if(have[i][j] == 1){
            return false;
        }
        if(word[lev] != board[i][j]){
            return false;
        }

        have[i][j] = 1;
        for(int k=0;k<4;k++){
            if(check(i+m[k][0], j+m[k][1], lev+1, board) == true){
                return true;
            }
        }
        have[i][j] = 0;
        return false;
    }

public:
    bool exist(vector<vector<char> > &board, string word) {
        if(board.size() == 0 || board[0].size() == 0 || word.size() == 0){
            return false;
        }
        x = board.size();
        y = board[0].size();
        this->word = word;
        init();
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(board[i][j] == word[0]){
                    reset();
                    if(check(i,j,0, board)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

void bornData(vector<string>&data, vector<vector<char> >&board){
    board.clear();
    for(int i=0;i<data.size();i++){
        vector<char>vec(data[i].begin(), data[i].end());
        board.push_back(vec);
    }
}

void output(vector<vector<char> >&board){

    for(int i=0;i<board.size();i++){
        vector<char>& vec = board[i];
        for(int j=0;j<vec.size();j++){
            printf("%c ", vec[j]);
        }
        printf("\n");
    }
    printf("\n");
}

void test(){
    Solution work;
    vector<vector<char> > board;
    string word;
    vector<string>data;
    int ans;
    
    data = {
        "ABCE",
        "SFCS",
        "ADEE",
    };
    bornData(data, board);
    output(board);
    
    word = "ABCCED";
    ans = work.exist(board, word);
    printf("word=%s ans=%d\n",word.c_str(), ans);
    
    word = "SEE";
    ans = work.exist(board, word);
    printf("word=%s ans=%d\n",word.c_str(), ans);
    
    word = "ABCB";
    ans = work.exist(board, word);
    printf("word=%s ans=%d\n",word.c_str(), ans);
}

int main() {
    test();
    return 0;
}
