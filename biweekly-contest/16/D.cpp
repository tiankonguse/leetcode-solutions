class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int len = board.size();
        board[0][0] = board[len-1][len-1] = '0'; //起点终点按0分处理
        
        //为了处理边界，下标从1开始
        vector<vector<pair<int, int>>> dp(len + 1, vector<pair<int, int>>(len + 1, {0, 0}));
        
        //起点之前再加一个起点
        dp[0][0] = {0, 1}; //{score, num}
        
        //合并计算逻辑
        auto add = [](auto& p, auto pre, int s){
            if(pre.second == 0) return;
            pre.first += s;
            if(pre.first > p.first){
                p = pre;
            }else if(pre.first == p.first){
                p.second = (p.second + pre.second) % 1000000007;
            }
        };
        
        for(int i=1;i<=len;i++){
            for(int j=1;j<=len;j++){
                if(board[i-1][j-1] == 'X') continue; //此路不通
                int s = board[i-1][j-1] - '0';
                pair<int, int> p = {0, 0};
                add(p, dp[i-1][j-1], s);
                add(p, dp[i][j-1], s);
                add(p, dp[i-1][j], s);
                if(p.first >= 0){
                    dp[i][j] = p; //有答案，赋值
                }
            }
        }
        auto p = dp[len][len];
        return {p.first, p.second};   
    }
};


