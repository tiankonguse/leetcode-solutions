/*************************************************************************
    > File Name: valid-sudoku.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月18日 星期六 16时25分37秒
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

    int have[10];

    void init(){
        memset(have, 0, sizeof(have));
    }

    bool checkRow(int r, vector<vector<char> >&board){
        init();
        if(board[r].size() != 9){
            return false;
        }

        int val = 0;
        for(int c=0;c<9;c++){
            switch(board[r][c]){
                case '.':break;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    val = board[r][c] - '0';
                    if(have[val] == 1){
                        return false;
                    }
                    have[val] = 1;
                    break;
                default:
                    return false;
                    break;
            }
        }

        return true;
    }

    bool checkColum(int c, vector<vector<char> >& board){
        init();
        int val = 0;
        for(int r=0;r<9;r++){
            switch(board[r][c]){
                case '.':break;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    val = board[r][c] - '0';
                    if(have[val] == 1){
                        return false;
                    }
                    have[val] = 1;
                    break;
                default:
                    return false;
                    break;
            }
        }
        return true;
    }

    bool checkGrid(int index, vector<vector<char> >& board){
        init();
        int val = 0;
        int x = (index/3) * 3;
        int y = (index%3) * 3;
        int r,c;

        for(int i=0;i<3;i++){
            r = x + i;
            for(int j=0;j<3;j++){
                c = y + j;
                switch(board[r][c]){
                    case '.':break;
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        val = board[r][c] - '0';
                        if(have[val] == 1){
                            return false;
                        }
                        have[val] = 1;
                        break;
                    default:
                        return false;
                        break;
                }
                
            }
        }

        return true;
    }

public:
    bool isValidSudoku(vector<vector<char> > &board) {

        if(board.size() != 9){
            return false;
        }


        for(int i=0;i<9;i++){
            if(!checkRow(i, board)){
                return false;
            }
        }

        for(int i=0;i<9;i++){
            if(!checkColum(i, board)){
                return false;
            }
        }

        for(int i=0;i<9;i++){
            if(!checkGrid(i, board)){
                return false;
            }
        }
        return true;
    }
};

void bornBoard(vector<string>&data, vector<vector<char> >& board){
    board.clear();
    for(int i=0;i<data.size();i++){
        int size = data[i].size();
        vector<char>line;
        for(int j=0;j<size;j++){
            line.push_back(data[i][j]);
        }
        board.push_back(line);
    }
    printf("next\n");
}


void output(vector<vector<char> >& board){
    int line = board.size();
    for(int i=0;i<line;i++){
        int row = board[i].size();
        for(int j=0;j<row;j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void test(){
    srand(time(NULL));
    Solution work;
    vector<string>data;
    vector<vector<char> >b;
    int ans;
    
    data.clear();
    data = {
        "53..7....",
        "6..195...",
        ".98....6.",
        "8...6...3",
        "4..8.3..1",
        "7...2...6",
        ".6....28.",
        "...419..5",
        "....8..79"
    };
    bornBoard(data, b);
    output(b);
    ans = work.isValidSudoku(b);
    printf("ans=%d\n",ans);

    data.clear();
    data = {
        ".87654321",
        "2........",
        "3........",
        "4........",
        "5........",
        "6........",
        "7........",
        "8........",
        "9........"
    };
    bornBoard(data, b);
    output(b);
    ans = work.isValidSudoku(b);
    printf("ans=%d\n",ans);


}

int main(){
    test();
    return 0;
}
