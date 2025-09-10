#include<bits/stdc++.h>
using namespace std;
//获取运算符的优先级
int getpri(char x) {
	if(x=='('){ //左括号级别最低 
		return 0;
	} 
	if(x=='+'||x=='-') {
		return 1;
	}
	if(x=='*'||x=='/') {
		return 2;
	}
}
int main() {
	char str[100];
	stack<char> st;
	cin.getline(str, 100); // 读取整个表达式
	int num = 0;
	int len = strlen(str);

	for(int i = 0; i < len; i++) { //从左向右遍历 
		if(str[i] >= '0' && str[i] <= '9') { // 处理数字
			cout<<str[i];
			cout<<" "; //直接输出当前数字
		} else if(str[i] == ' ') {
			continue;
		} else if(str[i]=='(') { //如果是左括号，则直接入栈
			st.push(str[i]);
		} else if(str[i]==')') { //如果是右括号，则依次出栈并输出，直到左括号为止
			while(st.top()!='(') {
				cout<<st.top()<<" ";
				st.pop();
			}
			st.pop(); //左括号出栈
		} else if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			//判定当前运算符和栈顶元素的优先级
			while((!st.empty())&&(getpri(st.top())>=getpri(str[i]))) { //栈顶元素优先级 大于 当前元素优先级，栈顶元素出栈
				cout<<st.top()<<" ";
				st.pop();
			}
			st.push(str[i]); // 将当前运算符入栈
		}
	}
	// 遍历结束后，弹出栈中剩余的运算符
	while(!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	return 0;
}
/*
测试用例：9+(3-1)*3+1/2
输出结果：9 3 1 - 3 * + 1 2 / + 

*/
