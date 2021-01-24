class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        
        //1、find level peoples
        map<int, int> have;
        queue<int> que;
        vector<int> peoples;
        auto addPeople = [&](auto _id, auto _level){
            if(have.count(_id)){
                return;
            }
            have[_id] = _level;
            if(_level < level){
                que.push(_id);
            }else if(_level == level){
                peoples.push_back(_id);
            }
        };
        
        addPeople(id, 0);
        while(!que.empty()){
            auto id = que.front();
            auto level = have[id];
            que.pop();
            for(auto newId: friends[id]){
                addPeople(newId, level + 1);
            }
        }
        
        //2、find level videos and count
        vector<string> ans;
        set<string> haveView;
        map<string, int> videoCount;
        
        auto addVideo = [&](string& v){
            videoCount[v]++;
            if(haveView.count(v) > 0){
                return;
            }
            haveView.insert(v);
            ans.push_back(v);
        };
        
        for(auto id: peoples){
            for(auto& v: watchedVideos[id]){
                addVideo(v);
            }
        }
        
        //sort by rule
        sort(ans.begin(), ans.end(), 
             [&videoCount](auto& v1, auto& v2){
                 
            if(videoCount[v1] == videoCount[v2]){
                return v1 < v2;
            }else{
                return videoCount[v1] < videoCount[v2];
            }
        });
        
        return ans;
    }
};
