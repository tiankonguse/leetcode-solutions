/*************************************************************************
    > File Name: problemset-new/000/00048-rotate-image/48-tiankonguse.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: Wed Jun 19 00:36:22 2019
 ************************************************************************/

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i=0;i<n;i++){
            for(int j=0;j<n-i;j++){
                int ni = n - 1 - j;
                int nj = n - 1 - i;
                swap(matrix[i][j], matrix[ni][nj]);
            }
        }
        
        for(int i=0;i<n/2;i++){
            for(int j=0;j<n;j++){
                int ni = n - 1 - i;
                int nj = j;
                swap(matrix[i][j], matrix[ni][nj]);
            }
        }
        
    }
};
