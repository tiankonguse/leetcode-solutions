class Solution {
    struct Node{
        int step, pos;
        pair<int,int> one, two;
        Node():step(0),pos(0){
            one = {-1, -1};
            two = {-1, -1};
        }
        bool operator<(const Node &t2) const{
            const Node &t1 = *this;
            if(t1.pos == t2.pos){
                if(t1.one == t2.one){
                    return t1.two < t2.two;
                }else{
                    return t1.one < t2.one;
                }                
            }else{
                return t1.pos < t2.pos;
            }
        }
        
    };
    struct cmp{
        bool operator()(const Node &t1, const Node &t2)const{
            if(t1.pos == t2.pos){
                return t1.step > t2.step;
            }else{
                return t1.pos > t2.pos;
            }
        }
    };
    int dis(const pair<int, int>& one, const pair<int, int>& two){
        return abs(one.first - two.first) + abs(one.second - two.second);
    }
    
    map<Node, int> m;
    bool have(Node node){
        int step = node.step;
        node.step = 0;
        if(m.count(node) == 0){
            m[node] = step;
            return false;
        }else if(m[node] <= step){
            return true;
        }else{
            m[node] = step;
            return false;
        }
    }
    void fix(Node& node){
        if(node.one > node.two){
            swap(node.one, node.two);
        }
    }
    
public:
    int minimumDistance(const string& w) {
        map<char, pair<int, int>> h;
        for(int i=0;i<26;i++){
            h[i+'A'] = {i/6, i%6};
        }
        
        priority_queue<Node, vector<Node>, cmp> que;
        que.push(Node());
        
        int ans = 26 * w.length();
        while(!que.empty()){
            const auto old = que.top();
            que.pop();
            
            char c = w[old.pos];
            Node newNode;
            //try one
            newNode.pos = old.pos + 1;
            if(old.one.first == -1){
                newNode.step = old.step;
            }else{
                newNode.step = old.step + dis(h[c], old.one);
            }
            newNode.one = h[c];
            newNode.two = old.two;
            if(newNode.pos == w.length()){
                ans = min(ans, newNode.step);
            }else{
                if(!have(newNode)){
                    fix(newNode);
                    que.push(newNode);
                }
            }
            
            //try two
            newNode.pos = old.pos + 1;
            if(old.two.first == -1){
                newNode.step = old.step;
            }else{
                newNode.step = old.step + dis(h[c], old.two);
            }
            newNode.one = old.one;
            newNode.two = h[c];
            if(newNode.pos == w.length()){
                ans = min(ans, newNode.step);
            }else{
                if(!have(newNode)){
                    fix(newNode);
                    que.push(newNode);
                }
            }
        }
        return ans;
    }
};
