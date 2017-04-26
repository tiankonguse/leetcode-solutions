/*************************************************************************
  > File Name: binary-tree-tilt.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com
***********************************************************************/


#include "../../include/base.h"


class Solution {
    struct TreeNodeInfo {
        TreeNodeInfo() {
            tilt = 0;
            sumVal = 0;
            sumTilt = 0;
        }
        int tilt;
        int sumVal;
        int sumTilt;
    };
	
    void findTilt(TreeNode* root, TreeNodeInfo& rootInfo) {
        if(root == NULL) {
            return;
        }
        TreeNodeInfo left;
        TreeNodeInfo right;
		
        findTilt(root->left, left);
        findTilt(root->right, right);
		
        rootInfo.sumVal = left.sumVal + right.sumVal + root->val;
        rootInfo.tilt = abs(left.sumVal - right.sumVal);
        rootInfo.sumTilt = left.sumTilt + right.sumTilt + rootInfo.tilt;

    }
public:
    int findTilt(TreeNode* root) {
        TreeNodeInfo rootInfo;
        findTilt(root, rootInfo);
        return rootInfo.sumTilt;
    }
};





int main() {
    Solution work;
    int ans = 0;

    TreeNode list[100];
    vector<Node> data;

    data = {
        {0, 1, -1, NODE_ROOT},
        {1, 2, 0, NODE_LEFT},
        {2, 3, 0, NODE_RIGHT},
    };
    memset(list, 0, sizeof(list));
    born(data, list);
    output(list);
    ans = work.findTilt(list);
    printf("ans=%d\n", ans);


    return 0;
}
