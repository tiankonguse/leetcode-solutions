class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        int len = arr.size();
        
        sort(arr.begin(), arr.end());
        
        vector<int> sumPre;
        sumPre.resize(len+1, 0);
        for(int i = 0, sum = 0; i < len; i++){
            sum += arr[i];
            sumPre[i+1] = sum;
        }
        
        int ansVal = 0;
        int ansSum = 0;
        
        int v = 0;
        for(int i = 0; i < len && v <= arr.back(); v++){
            while(i < len && v > arr[i]){
                i++;
            }
            int tmp = sumPre[i] + v * (len - i);
            if(abs(ansSum - target) > abs(tmp - target)){
                ansSum = tmp;
                ansVal = v;
            }
            
        }
        return ansVal;
    }
};


