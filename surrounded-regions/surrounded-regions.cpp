/*************************************************************************
    > File Name: surrounded-regions.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月22日 星期三 23时22分40秒
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
    int x;
    int y;
    int m[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    vector<vector<int> >have;
    char O ;
    char X ;
    char T;

    struct Dot{
        int x;
        int y;
        Dot(int x=0, int y=0):x(x),y(y){

        }
    };

    void init(){
        O = 'O';
        X = 'X';
        T = 'T';        
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
    
    bool check(int i, int j, vector<vector<char> >&board){

        stack<Dot>sta;
        sta.push(Dot(i,j));
        Dot now;

        while(!sta.empty()){
            now = sta.top();
            sta.pop();
            have[now.x][now.y] = 1;

            for(int k=0;k<4;k++){
                i = now.x + m[k][0];
                j = now.y + m[k][1];
                if(i<0 || j<0 || i >= x || j >= y){
                    return false;
                }
                if(have[i][j]){
                    continue;
                }
                if(board[i][j] != O){
                    continue;
                }
                sta.push(Dot(i,j));
            }

        }

        return true;
    }

    void captured(int i, int j, vector<vector<char> >&board, char C){
        stack<Dot>sta;
        sta.push(Dot(i,j));
        Dot now;
        
        while(!sta.empty()){
            now = sta.top();
            sta.pop();
            board[now.x][now.y] = C;
            for(int k=0;k<4;k++){
                i = now.x + m[k][0];
                j = now.y + m[k][1];
                if(i<0 || j<0 || i >= x || j >= y){
                    continue;
                }
                if(board[i][j] != O){
                    continue;
                }
                sta.push(Dot(i,j));
            }
        }
    }

    void recovery(vector<vector<char> >&board){
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(board[i][j] == T){
                    board[i][j] = O;
                }
            }
        }
    }

public:
    void solve(vector<vector<char>> &board) {
        if(board.size() == 0 || board[0].size() == 0){
            return ;
        }
        x = board.size();
        y = board[0].size();
        init();
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(board[i][j] == O){
                    if(check(i,j, board)){
                        captured(i,j, board, X);
                    }else{
                        captured(i,j, board, T);
                    }
                }
            }
        }
        recovery(board);
    }
};

void output(vector<vector<char> >&board){
    for(int i=0;i<board.size();i++){
        vector<char>& vec = board[i];
        for(int j=0;j<vec.size();j++){
            printf("%c ", vec[j]);
        }
        printf("\n");
    }
}

void bornData(vector<string>&data, vector<vector<char> >&board){
    board.clear();
    for(int i=0;i<data.size();i++){
        vector<char> vec(data[i].begin(), data[i].end());
        board.push_back(vec);
    }
}

void test(){
    srand(time(NULL));
    Solution work;

    vector<vector<char>> board;
    vector<string>data;

    data = {
        "XXXX",
        "XOOX",
        "XXOX",
        "XOXX",
    };
    bornData(data, board);
    output(board);
    work.solve(board);
    output(board);

    data = {
        "OOOO",
        "OOOO",
        "OOOO",
        "OOOO",
    };
    bornData(data, board);
    output(board);
    work.solve(board);
    output(board);

}

int main(){
    test();
    return 0;
}
