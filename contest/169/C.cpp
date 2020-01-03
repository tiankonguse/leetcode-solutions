class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        queue<int> que;
        set<int> s;
        auto addAndCheck = [&](int pos){
            if(pos < 0 || pos >= arr.size()){
                return false;
            }
            if(arr[pos] == 0) return true;
            if(s.count(pos) == 0){
                que.push(pos);
                s.insert(pos);
            }
            return false;
        };
        if(addAndCheck(start)){
            return true;
        }
        while(!que.empty()){
            int now = que.front();que.pop();
            if(addAndCheck(now - arr[now])){
                return true;
            }
            if(addAndCheck(now + arr[now])){
                return true;
            }
        }
        return false;
    }
};


