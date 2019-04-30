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
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {}
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
class Solution {
    map<Node*, Node*>m;
    Node* clone(Node* node) {
        Node* newNode;
        newNode = new Node();
        newNode->val = node->val;
        m[node] = newNode;
        return newNode;
    }
    Node* dfs(Node* node) {
        stack<pair<Node*, Node*>> sta;
        Node* root;
        root = clone(node);
        sta.push(make_pair(root, node));

        while(!sta.empty()) {
            auto newNode = sta.top().first;
            auto oldNode = sta.top().second;
            sta.pop();
            for(int i=0; i<oldNode->neighbors.size(); i++) {
                auto oldChildNode = oldNode->neighbors[i];
                Node* newChildNode;
                if(m.find(oldChildNode) != m.end()) {
                    newChildNode = m[oldChildNode];
                } else {
                    newChildNode = clone(oldChildNode);
                    sta.push(make_pair(oldChildNode, newChildNode));
                }
                newNode->neighbors.push_back(newChildNode);
            }
        }
        return root;
    }

public:
    Node *cloneGraph(Node *node) {
        if(node == NULL) {
            return NULL;
        }
        return dfs(node);
    }
};

struct Node {
    int index;
    int label;
    vector<int> child;
    Node() {

    }
    Node(int index, int label, vector<int>&child):index(index), label(label), child(child) {

    }
};


void born(vector<vector<int> >&data, UndirectedGraphNode* list) {
    int l = data.size();
    for(int j=0; j<l; j++) {
        int index = data[j][0];
        int label = data[j][1];
        int size = data[j].size();
        printf("label=%d  (%p)\n", label, list + index);
        list[index].label = label;
        for(int i=2; i<size; i++) {
            list[index].neighbors.push_back(list + data[j][i]);
            printf("    %d  (%p)\n", data[j][i], list + data[j][i]);
        }
    }
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
}


void output(UndirectedGraphNode* root) {
    printf("label=%d  (%p)\n", root->label, root);
    vector<UndirectedGraphNode *>& neighbors = root->neighbors;
    int size = neighbors.size();
    for(int i=0; i<size; i++) {
        printf("    %d  (%p)\n", neighbors[i]->label, neighbors[i]);
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

void test() {
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

int main() {
    test();
    return 0;
}
