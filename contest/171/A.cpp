class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        int a = 0, b = 0, base = 1;
        while(n > 0){
            int bit = n % 10;  
            n = n/10;
            if(bit > 1){
                a += base * 1;
                b += base * (bit - 1);
            }else{ // bit in [0, 1]，借位
                if(n == 0){ //bit = 1
                    a += base * 1;
                }else{
                    a += base * 2;
                    b += base * (8 + bit);
                    n--;
                }
            }
            base = base * 10;
        }
        return {a, b};
    }
};


