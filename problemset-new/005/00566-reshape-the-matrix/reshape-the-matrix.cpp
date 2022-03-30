	/**********	***************************************************************
  > File Name: reshape-the-matrix.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
***********************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        vector<int> oneMatrix;
		int col = nums.size();
		int row = nums[0].size();
		if(col * row != r * c){
			return nums;
		}
		
		for(int i = 0; i < col; i++){
			for(int j = 0; j < row; j++){
				oneMatrix.push_back(nums[i][j]);
			}
		}
		vector<vector<int>> ans;
		int index = 0;
		for(int i = 0; i < r; i++){
			vector<int> oneLine;
			for(int j = 0; j < c; j++){
				oneLine.push_back(oneMatrix[index++]);
			}
			ans.push_back(oneLine);
		}
		return ans;
    }
};

void test(vector<vector<int>>& input, int r, int c){
	Solution work;
	vector<vector<int>> ans = work.matrixReshape(input, r, c);
	printf("input: r = %d c = %d matrix = \n", r, c);
	output(input);
	printf("ans = \n");
	output(ans);
}

int main() {
	int r,c;
	
	vector<vector<int>> input = {{1,2},{3,4}};
	r = 1;
	c = 4;
	test(input, r, c);
	
	
	r = 2;
	c = 4;
	test(input, r, c);
	
    return 0;
}
