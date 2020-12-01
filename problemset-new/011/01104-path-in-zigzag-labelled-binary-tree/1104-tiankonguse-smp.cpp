/*************************************************************************
    > File Name: problemset-new/011/01104-path-in-zigzag-labelled-binary-tree/tiankonguse-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2019年06月30日 20:52:51
 ************************************************************************/

class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        vector<int> ans;
        
        int right = 1;
        while(right <= label){
            right <<= 1;
        }
        while(label > 0){
            ans.push_back(label);
            right /= 2;
            label = right/2 + (right - 1) - label/2;
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

