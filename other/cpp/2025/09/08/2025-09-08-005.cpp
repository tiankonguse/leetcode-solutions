#include<bits/stdc++.h>
// 前缀表达式求值（多位实数）

using namespace std;
//进行运算操作
double solve(double x,double y,char op) {
	switch(op) {
		case '+':
			return y+x; //注意这里两个数字的顺序
		case '-':
			return y-x;
		case '*':
			return y*x;
		case '/':
			return y*1.0/x;
	}
}
int main() {
	char str[100];  //存储表达式
	stack<double> st; //栈
	cin.getline(str,100);//以行输入读
	double num=0;//存储每个数字
	int len=strlen(str);
	bool dot=false; //标记是否遇到小数点 
	double dec=0.1;//小数部分因子 
	for(int i=len-1; i>=0; i--) {
		if(str[i]>='0'&&str[i]<='9'||str[i]=='.') { //如果是数字或者小数点
			continue; 
		}
		else if(str[i]==' ') {
			    int flag=i++; //记录 
				num=0; //重置为0 
				dot=false;
				dec=0.1;
		} else if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'){ //如果是运算符，依次出战两个数字
			double x=st.top(); //取栈顶数字
			st.pop();
			double y=st.top(); //取第二个栈顶数字
			st.pop();
			//进行运算
		
			double ans=solve(x,y,str[i]);
			st. push(ans); //入栈
		}
	}
	printf("%.3lf\n",st.top()); //最终栈顶元素就是答案
	return 0;
}
/*
13.0 3.2 8 + 4 * *

582.400
*/
