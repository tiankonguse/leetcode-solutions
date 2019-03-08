#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

/**
 * Definition for a binary tree node.
 */

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x = 0) : val(x), left(NULL), right(NULL) {}
};

enum {
    NODE_LEFT = 0,
    NODE_RIGHT = 1,
    NODE_ROOT = -1,
};

struct Node {
	int index;
	int val;
	int pre;
	int type; // 0 left, 1 right , -1 root
	Node(int index=-1, int val = -1, int pre = -1, int type = -1):index(index), val(val), pre(pre), type(type) {

	}
};

/*
 *  TreeNode list[100];
 *  vector<Node> data;
 *
 *      0
 *     / \
 *    1   2
 *  data = {
 *      {0, 0, -1, NODE_ROOT},
 *      {1, 1, 0, NODE_LEFT},
 *      {2, 2, 0, NODE_RIGHT},
 *  };
 *  memset(list, 0, sizeof(list));
 *  born(data, list);
 *
 */
void born(vector<Node>&data, TreeNode* root) {
	for(vector<Node>::iterator it = data.begin(); it != data.end(); it++) {
		int index = it->index;
		int val = it->val;
		int pre = it->pre;
		int type = it->type;

		root[index].val = val;
		if(pre != -1) {
			if(type == 0) {
				root[pre].left = root + index;
			} else if(type == 1) {
				root[pre].right = root + index;
			} else {
				printf("WARNING: data error. type = %d\n", type);
			}
		}
	}
}

void output(TreeNode* root, int lev=0, int pre = -1) {
	printf("lev = %d pre = %d addr = %p\n", lev, pre, root);
	if(root != NULL) {
		output(root->left, lev+1, root->val);
		output(root->right, lev+1, root->val);
	}
}

void output(char data){
    printf("%c ", data);
}

void output(int data){
    printf("%d ", data);
}

void output(long long data){
    printf("%lld ", data);
}

void output(string& data){
    printf("%s ", data.c_str());
}

template <class baseType>
void output(vector<baseType>& vec){
	for(int i = 0; i < vec.size(); i++){
		output(vec[i]);
	}
	printf("\n");
}

template <class baseType>
void output(vector<vector<baseType>>& matrix){
	for(int i = 0; i < matrix.size(); i++){
		output(matrix[i]);
	}
	printf("\n");
}

template <class baseType>
void output(char const* name,baseType data) {
    printf("%s:", name);
    output(data);
    printf("\n");
}
template <class baseType>
void output(char const* name,vector<baseType> data) {
    printf("%s size[%d]:\n    ", name, data.size());
    output(data);
    printf("\n");
}

template <class vecType>
void output(char const* name,vector<vector<vecType> > data) {
    printf("%s size[%d]:\n", name, data.size());
    for(int i=0; i<data.size(); i++) {
        output("    ", data[i]);
    }
    printf("\n");
}

template <class baseType>
bool eq(baseType first, baseType second){
    return first == second;
}

template <class baseType>
bool eq(vector<baseType> first, vector<baseType> second){
    if(first.size() != second.size()){
        return false;
    }
    for(int i=0; i<first.size(); i++) {
        if(!eq(first[i], second[i])){
            return false;
        }
    }
    return true;
}


template <class baseType>
bool eq(vector<vector<baseType>> first, vector<vector<baseType>> second){
    if(first.size() != second.size()){
        return false;
    }
    for(int i=0; i<first.size(); i++) {
        if(!eq(first[i], second[i])){
            return false;
        }
    }
    return true;
}

