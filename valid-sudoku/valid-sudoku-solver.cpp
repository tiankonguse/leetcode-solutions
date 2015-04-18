/*************************************************************************
    > File Name: valid-sudoku.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月18日 星期六 13时47分16秒
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
        
        
        
const int maxm = 4004;
const int maxn = 906;
class DLX{
    
    int R[maxm];//right link
    int L[maxm];//left link
    int U[maxm];//up link
    int D[maxm];// down link
    
    int col[maxm];// colum head link
    int row[maxm];// row head link
    
    int s[maxn];//当前列元素个数
    bool hash[maxn]; //重复覆盖
    
    int pre;//前一行,初始值-1,代表没有行
    
    int first;//由于每一行都是个循环双向列表, first需要标记当前行的第一个元素的位置
    
    //使用数组模拟矩阵, 代表当前使用的内存空间 初始值占用行头
    int sz;
    
    int limit;
    
    int used[maxn];//标记 行 是否 选择
    
public:
    
    //初始化, n代表列数
    void init(int n){
        sz = 0;
        pre = -1;
        
        first = 0;
        
        memset(used,0,sizeof(used));
        
        for(int i = 0;i <= n;i ++){
            U[i] = i;
            D[i] = i;
            col[i] = i; 
            L[i] = i-1,
            R[i] = i+1;
            sz++;
        }
        
        memset(s,0,sizeof(s));
    }

    //上一行的最后一个元素指向第一个元素
    //上一行的第一个元素指向最后一个元素
    void finishRow(){
        int head = first;
        int tail = sz-1;
        
        R[tail] = head;
        L[head] = tail;
    }
    
    //一行一行的插入数据i行j列
    void insert(int i,int j) {   
        //pre表示前一行，如果不同，就更新前面那行的左右
        if(i != pre) {
            finishRow();
            pre = i;
            first = sz;
        }
        L[sz] = sz - 1;
        R[sz] = sz+1;  
        
        //j 是列头, 由于垂直方向也是双向循环列表,所以列头的UP就是这一列行尾
        //新增的元素肯定是是这一列的行尾
        D[sz] = j;
        U[sz] = U[j];
        D[U[sz]] = sz;//旧的列尾后面追加当前元素
        U[D[sz]] = sz;//列头指向新增元素
        
        row[sz] = i;
        col[sz] = j,
        
        s[j] ++;
        
        sz ++;
    }
    //选择行，使每一列仅有一个
    //精确覆盖，选择了k行了。
    bool dfs(const int &k) {
        if(R[0] == 0){
            return true;
        }
        
        int idx = findMinCol();
        
        EXremove(col[idx]);
        
        for(int i = D[idx];i != idx;i = D[i]){
            used[row[i]] = 1;
            
            for(int j = R[i];j != i;j = R[j]){
                EXremove(col[j]);
            }
            
            if(dfs(k+1)){
                return true;  
            }
            
            for(int j = L[i];j != i;j = L[j]){
                EXresume(col[j]);
            }
            used[row[i]] = 0;
        }
        
        EXresume(col[idx]);
        return false;
    }

private:
    //删除c列,而且与c有重复的行精确覆盖
    void EXremove(int c){    
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        
        //从上到下,从左到右遍历删除每一行
        for(int i = D[c];i != c;i = D[i]){
            for(int j = R[i];j != i;j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --s[col[j]];
            }
        }
    }
    
    //恢复c列,而且与c有重复的行
    void EXresume(int c){  
       for(int i = U[c];i != c;i = U[i]){
           for(int j = L[i];j != i;j = L[j]) {
                ++s[col[j]];
                U[D[j]] = j;
                D[U[j]] = j;
            }
       }
        L[R[c]] = c;
        R[L[c]] = c;
    }
    
    int findMinCol(){
        int idx = R[0];
        for(int i = R[0] ;i != 0;i = R[i]){
            if(s[idx] > s[i]){
                idx = i;
            }
        }
        
        return idx;
    }
    
    
    //重复覆盖,选择最少行，所有的列被覆盖,后来添加的。
    void remove(int & c) { 
        for(int i = D[c];i != c;i = D[i]){
            L[R[i]] = L[i];
            R[L[i]] = R[i]; 
        }
    } 
    
    void resume(int & c) { 
        for(int i = U[c];i != c;i = U[i]){
            L[R[i]] = i;
            R[L[i]] = i; 
        }
    }
    
    //f启发函数
    int h(){  
        int ret = 0;
        memset(hash,false,sizeof(hash));
        for(int c = R[0];c != 0;c = R[c]){
            if(!hash[c]){
                hash[c] = true;  
                ret ++;
                for(int i = D[c];i != c;i = D[i]){
                    for(int j = R[i];j != i;j = R[j]){
                        hash[col[j]] = true;
                    }
                }
                    
            }
        }
        return ret;
    }
    
    //重复覆盖，只删除列不删除行
    bool dfs(const int & k,int & limit){
        if(k+h() >= limit){
             return false;
        }
        
        if(R[0] == 0){
            if(k < limit){
                limit = k; 
            }
            
            return true;
        }
        
        int idx = findMinCol();
        
        for(int i = D[idx];i != idx;i = D[i]){
            remove(i);
            
            for(int j = R[i];j != i;j = R[j]){
                remove(j);
            }
            
            if(dfs(k+1,limit)){
                return true;
            }
            
            for(int j = L[i];j != i;j = L[j]){
                resume(j);
            }
            
            resume(i);
        }
        return false;
    }
    
    //IDX*
    int astar() {
        limit = h();
        //修改点，limit最后期限
        while(!dfs(0,limit)){
            limit++;  
        }
        return limit;
    }
};

class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        DLX dlx;
        dlx.init(324);
        int dlxRow = 1;
        int number= 0; 
        int Max = 9;
        
        for(int i=0;i<Max;i++){
            for(int j=0;j<Max;j++){
                if(board[i][j] == '.'){
                    //blank
                    for(int k = 1;k <= Max;k ++){
                        dlx.insert(dlxRow,i * Max + k);  //行+数字
                        dlx.insert(dlxRow,81+j*Max+k); //列+数
                        dlx.insert(dlxRow,162+(i/3 + (j/3) *3 ) * Max+k); //小方块号号
                        dlx.insert(dlxRow,243+i*Max+j+1); //座位
                        dlxRow++;
                    }
                }else{
                    //number
                    number = board[i][j] - '0';
                    dlx.insert(dlxRow,i*Max+number);  //行+数字
                    dlx.insert(dlxRow,81+j*Max+number); //列+数
                    dlx.insert(dlxRow,162+(i/3+(j/3)*3)*Max+number); //小方块号
                    dlx.insert(dlxRow,243+i*Max+j+1); //座位
                    dlxRow++;
                }
            }
        }
        
        dlx.finishRow();
        
        if(dlx.dfs(0)){
            return true;
        }else{
            return false;
        }
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
