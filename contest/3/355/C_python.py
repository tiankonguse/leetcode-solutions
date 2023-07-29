class Solution:
    def maxIncreasingGroups(self, usageLimits: List[int]) -> int:
        ul = sorted(usageLimits)
        print(ul)
        remain = 0 # 前面数组多余的数量
        require = 1 # 最小目标序列需要的长度，从1~n
        for num in ul:
            remain += num
            if remain >= require: # 如果当前位置积累的数量达到了目标序列的要求
                remain -= require 
                require += 1 
        return require - 1