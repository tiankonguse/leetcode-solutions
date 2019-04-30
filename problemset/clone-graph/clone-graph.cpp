/*************************************************************************
    > File Name: clone-graph.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月22日 星期三 01时44分04秒
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
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x=0) : label(x) {};
};
class Solution {
    map<int, UndirectedGraphNode*>m;

    UndirectedGraphNode* _copy(UndirectedGraphNode* node){
        int label = node->label;

        if(m.find(label) != m.end()){
            return m[label];
        }

        UndirectedGraphNode* newNode;
        if(m.find(label) == m.end()){
            newNode  = new UndirectedGraphNode(label);
            m[label] = newNode;
        }else{
            newNode = m[label];
        }

        int size = node->neighbors.size();
        UndirectedGraphNode* neighborNode; 

        for(int i=0;i<size;i++){
            neighborNode = _copy(node->neighbors[i]);
            newNode->neighbors.push_back(neighborNode);
        }

        return newNode;
    }

public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL){
            return NULL;
        }
        UndirectedGraphNode* ans =  _copy(node);
        return ans;
    }
    ~Solution(){
        for(map<int, UndirectedGraphNode*>::iterator it = m.begin(); it != m.end(); it++){
            //delete it->second;
        }
    }
};

struct Node{
    int index;
    int label;
    vector<int> child;
    Node(){

    }
    Node(int index, int label, vector<int>&child):index(index), label(label), child(child){

    }
};


void born(vector<vector<int> >&data, UndirectedGraphNode* list){
    int l = data.size();
    for(int j=0;j<l;j++){
        int index = data[j][0];
        int label = data[j][1];
        int size = data[j].size();
        printf("label=%d  (%p)\n", label, list + index);
        list[index].label = label;
        for(int i=2;i<size;i++){
            list[index].neighbors.push_back(list + data[j][i]);
            printf("    %d  (%p)\n", data[j][i], list + data[j][i]);
        }
    }
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
}


void output(UndirectedGraphNode* root){
    printf("label=%d  (%p)\n", root->label, root);
    vector<UndirectedGraphNode *>& neighbors = root->neighbors;
    int size = neighbors.size();
    for(int i=0;i<size;i++){
        printf("    %d  (%p)\n", neighbors[i]->label, neighbors[i]);
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

void test(){
    srand(time(NULL));
    Solution work;

    UndirectedGraphNode list[100];
    
    vector<vector<int> > data;

    UndirectedGraphNode* ans;

    data.clear();
    data = {
        {0,0,1,2},
        {1,1,2},
        {2,2,2},
    };
    born(data, list);
    output(list);
    ans = work.cloneGraph(list);
    output(ans);

}

int main(){
    test();
    return 0;
}
