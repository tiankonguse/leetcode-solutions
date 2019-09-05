class Solution {
    const int MOD = 1000000000 + 7;
    int getPrime(int n){
        int num = 0;
        for(int i=2;i<=n;i++){
            bool is = true;
            for(int j=2;j<i;j++){
                if(i%j == 0){
                    is = false;
                    break;
                }
            }
            if(is)num++;
        }
        return num;
    }
    long long jiecheng(int n){
        if(n<=1)return 1;
        long long ans = 1;
        while(n>0){
            ans = ans * n % MOD;
            n--;
        }
        return ans;
    }
public:
    int numPrimeArrangements(int n) {
        if(n==1 || n == 2)return 1;
        int x = getPrime(n);
        return jiecheng(x) * jiecheng(n - x) % MOD;
    }
};

