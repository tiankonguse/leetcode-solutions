# 1106. Parsing A Boolean Expression  


题意：给一个布尔表达式的规则，求表达式对应的值。  

这道题其实和上周比赛的最后一题非常类似，这是上次我的题解。  
Leetcode 第142场比赛回顾: https://mp.weixin.qq.com/s/Q3IugqcNwP8n82sGn0kRLA  

布尔表达式有`5`个规则。  

1. `t`为真 
2. `f`为假
3. `!(expr)` 取反  
4. `&(expr,expr,...)` 取与  
5. `|(expr,expr,...)` 取或  

我们可以增加另外一个规则，就可以形成递归闭环。  

6. `(expr,expr,...)` 获得布尔表达式集合。  

有了第`6`个万能的规则，代码实现就非常简单了
当然，实际上我们并没有必要求出集合，只需要统计是否有true和是否有false即可。  



