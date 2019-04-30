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
	
	//由于求最大值和最小值合并了通用逻辑，所以理解难度大点，大家可以使用其中一个模拟一下
	long long getNearestAns(const long long inputNum, const int sign, const char baseChar){
		char inputBuffer[20];
		const int inputLength = snprintf(inputBuffer, sizeof(inputBuffer), "%lld", inputNum);
		
		//个位数自身就是回文串
		if(inputNum <= 9){
			return inputNum; 
		}	
		
		//对10幂数特殊判断，10^幂+1和10^幂-1肯定都是回文串
		if(isTenPower(inputBuffer, inputLength)){
			//小答案刚好减一， 大答案刚好加1
			return inputNum + sign;
		}
		
		char ansBuffer[20];
		//小答案填充0，因为这里只是判断是否存在解，越小越好，极值是0
		//大答案填充9，因为这里只是判断是否存在解，越大越好，极值是9
		memset(ansBuffer, baseChar, sizeof(ansBuffer));
		ansBuffer[inputLength] = '\0';
		
		for(int begin = 0, end = inputLength - 1; begin <= end; begin++, end--){
			//小答案是求最大值，所以需要从9迭代，大答案求最小值，所以从0迭代
			char c = baseChar -  9 * sign;
			for(int i=0; i < 10; i++,c += sign){
				ansBuffer[begin] = ansBuffer[end] = c;
				//第一个解是当前位置的最优解
				//比如对于小答案，是求最大值，所以ABCD8为前缀的答案肯定比ABCD6为前缀的答案更优
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
