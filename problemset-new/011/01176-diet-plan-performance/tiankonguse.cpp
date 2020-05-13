class Solution {
public:
    int dietPlanPerformance(
        vector<int>& calories, 
        int k, int lower, int upper) {
        int ans = 0;
        
        int sum = 0;
        for(int i=0;i<k-1;i++){
            sum += calories[i];
        }
        for(int i=k-1;i<calories.size();i++){
            sum += calories[i];
            if(sum > upper)ans++;
            if(sum < lower)ans--;
            sum -= calories[i-(k-1)];
        }
        
        return ans;
    }
};


