class Solution {
    
public:
    int makeConnected(int n, vector<vector<int>>& edges) {
        if(n -1 > edges.size()){
            return -1;
        }
        map<int, vector<int>> m;
        for(auto& p: edges){
            m[p[0]].push_back(p[1]);
            m[p[1]].push_back(p[0]);
        }
        
        int group = 0;
        set<int> have;
        queue<int> que;
        for(int i=0;i<n;i++){
            if(have.count(i)) continue;
            group++;
            
            que.push(i);
            have.insert(i);
            while(!que.empty()){
                int now = que.front();
                que.pop();
                for(auto v: m[now]){
                    if(have.count(v)) continue;
                    que.push(v);
                    have.insert(v);
                }
            }
        }
        return group - 1;
    }
};


