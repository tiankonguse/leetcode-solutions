	/**********	***************************************************************
  > File Name: find-the-closest-palindrome.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
***********************************************************************/

#include "../../include/base.h"

class Solution {
	//10幂数不是回文串。10^幂+1和10^幂-1肯定都是回文串
	bool isTenPower(char* inputBuffer, int inputLength){
		if(inputBuffer[0] != '1'){
			return false;
		}
		for(int i = 1; i < inputLength; i++){
			if(inputBuffer[i] != '0'){
				return false;
			}
		}
		return true;
	}
	
	long long getNearestAns(const long long inputNum, const int sign, const char baseChar){
		char inputBuffer[20];
		const int inputLength = snprintf(inputBuffer, sizeof(inputBuffer), "%lld", inputNum);
		
		if(inputNum <= 9){//个位数自身就是回文串
			return inputNum; 
		}	
		
		if(isTenPower(inputBuffer, inputLength)){//对10幂数特殊判断，10^幂+1和10^幂-1肯定都是回文串
			return inputNum + sign;
		}
		
		char ansBuffer[20];
		memset(ansBuffer, baseChar, sizeof(ansBuffer));
		ansBuffer[inputLength] = '\0';
		
		for(int begin = 0, end = inputLength - 1; begin <= end; begin++, end--){
			char c = baseChar -  9 * sign;
			for(int i=0; i < 10; i++,c += sign){
				ansBuffer[begin] = ansBuffer[end] = c;
				if(strncmp(ansBuffer, inputBuffer, inputLength) * sign >= 0){
					break;
				}
			}
		}
		return atoll(ansBuffer);
	}
	
	//得到小于等于inputNum的最大的回文串
	long long getNearestSmallAns(const long long inputNum){
		return getNearestAns(inputNum, -1, '0');
	}
	//得到大于等于inputNum的最小的回文串
	long long getNearestBigAns(const long long inputNum){
		return getNearestAns(inputNum, 1, '9');
	}
public:
    std::string nearestPalindromic(const std::string& n) {
		long long inputNum = atoll(n.c_str());
		//printf("inputnum = %lld\n", inputNum);
        long long smallAns = getNearestSmallAns(inputNum - 1);
		long long bigAns = getNearestBigAns(inputNum + 1);
		
		
		//printf("smallAns = %lld\n", smallAns);
		//printf("bigAns = %lld\n", bigAns);
		long long smallAnsDis = inputNum - smallAns;
		long long bigAnsDis = bigAns - inputNum;
		
		long long ans = 0;
		if(smallAnsDis <= bigAnsDis){
			ans = smallAns;
		}else{
			ans = bigAns;
		}
		
		char buffer[20];
		snprintf(buffer, sizeof(buffer), "%lld", ans);
		return buffer;
    }
};




int main() {
	Solution work;
	string ans;
	string input;
	char buffer[20] = "123";
	
	while(~scanf("%s", buffer)){
		input = buffer;
		ans = work.nearestPalindromic(input);
		printf("Input: \"%s\"\nOutput: \"%s\"\n", input.c_str(), ans.c_str());
	}

    return 0;
}
