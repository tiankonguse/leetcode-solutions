#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
int isprime[N + 1];
int p[N];
int ct = 0;
int main() {
  memset(isprime, 1, sizeof(isprime));
  for (int i = 2; i <= N; i++) {
    /*
	   需要证明：如果 i 是 合数，一定会在 i 之前被筛掉
	   举例：当前 i= 12，需要证明在 i= [2,11] 时，一定可以把 12 标记为合数
	   i(12) = a1*k1 * a2*k2 * a3*k3 * ... * an*kn // a1 < a2 < a3 <... < ak
	     = a1 * (a1*(k1-1) * a2*k2 * a3*k3 * ... * ak*kn) 
		 = a1 * j
	   令 j = (a1*(k1-1) * a2*k2 * a3*k3 * ... * ak*kn)
	   结论：任何一个合数，都会被它的最小素因子筛掉

	   推论：枚举素数列表时，只需要枚举到第一个素因子即可
    */
    if (isprime[i]) {  // 证明1：为啥这一步是正确的？
      p[ct++] = i;
    }
	
    for (int j = 0; j < ct && i * p[j] <= N; j++) { // 从小到大枚举素数列表
	  isprime[i * p[j]] = 0;
      if (i % p[j] == 0) {
        break; // 后面的数不需要处理，也可以保证正确性
      }
    }
  }
  for (int i = 0; i < ct; i++) {
    printf("%d\n", p[i]);
  }
  return 0;
}

/*
p[] 是素数列表 2,3,5,...
问题：怎么找到数字 i 的最小素因子？

每个数字只有一个最小素因子
反证法：假设 p1 * i 把 X 筛掉， p2 * j 又把 X 筛掉。
X = p1 * i = p2 * j
i = p2 * p3
j = p1 * p4

X = p1 * p2 * p3 = p2 * p1 * p4
得：p3 = p4
X 的质因子列表为 p1 < p2 < p3
肯定会在 i = X/p1 时，把 X 筛掉，不会在 p2 筛

但 X 只有一个素因子，要么是 p1 要么是 p2。

*/

/*

i 之前的所有自然数 都已经乘以 i 之前的所有素数了

i % p[j] = 0	 //i % p[j] == 0 说明 i 肯定不是素数
i = a0^k0 * a1^k1 * a2^k2 * ... * an^kn // a0 < a1 < a2 < ... < an <= i
则 p[j] = a0
令 p[j+1] = ak, 则 a0 < ak <= an

//只需要证明，在后面一定会被筛掉（I > i）

i * ak
= a0^k0 * a1^k1 * a2^k2 * ... * an^kn * ak
= a0^k0 * a1^k1 * a2^k2 * ... ak*kk * ... * an^kn
= a0^k0 * a1^k1 * a2^k2 * ... ak*(kk+1) * ... * an^kn
= a0 * (a0^(k0-1) * a1^k1 * a2^k2 * ... ak*(kk+1) * ... * an^kn)
= a0 * X // 在 X 的时候，一定可以把这个数字筛掉
X = a0^(k0-1) * a1^k1 * a2^k2 * ... ak*(kk+1) * ... * an^kn

筛法：(p1, p2, p3, ..., pn) X (2, 3, 4, 5，...)
埃筛：枚举 (p1, p2, p3, ..., pn)， 乘以所有 (2, 3, 4, 5，...)
欧筛：枚举 (2, 3, 4, 5，...)， 乘以所有 (p1, p2, p3, ..., pn)

2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103
107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211
223 227 229 233 239 241251 257 263 269 271 277 281 283

i=6
p = 2,3,5

18: 9 * 2
枚举到一个合数，a*b，怎么证明前面一定会被筛掉呢？



*/