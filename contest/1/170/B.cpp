class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, 
                   vector<vector<int>>& queries) {
        vector<int> ans;
        vector<int> sum;
        
        int pre = 0;
        sum.push_back(pre);
        for(auto v: arr){
            pre = pre ^ v;
            sum.push_back(pre);
        }
        
        for(auto q: queries){
            ans.push_back(sum[q[1]+1] ^ sum[q[0]]);
        }
        return ans;
    }
};


