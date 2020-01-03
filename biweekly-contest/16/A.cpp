class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        vector<int> ans;
        int maxVal = -1;
        ans.resize(arr.size(), -1);
        for(int i = arr.size() - 1; i >= 0; i--){
            ans[i] = maxVal;
            maxVal = max(maxVal, arr[i]);
        }
        return ans;
    }
};


