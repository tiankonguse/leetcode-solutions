from collections import Counter
from functools import lru_cache

MAX = 10005
factorial = [1] * MAX
for i in range(1, MAX):
    factorial[i] = factorial[i - 1] * i

@lru_cache(maxsize=None)
def count_permutations(freq_tuple):
    total = sum(freq_tuple)
    res = factorial[total]
    for f in freq_tuple:
        res //= factorial[f]
    return res

def kth_smallest_permutation(s, k):
    counter = Counter(s)
    chars = sorted(counter.keys())
    freq_tuple = tuple(counter[c] for c in chars)
    total_possible = count_permutations(freq_tuple)
    if k > total_possible:
        return ""  # 所有合法排列数不足 k 个

    result = []
    while len(result) < len(s):
        for ch in chars:
            if counter[ch] == 0:
                continue
            counter[ch] -= 1
            freq_tuple = tuple(counter[c] for c in chars)
            cnt = count_permutations(freq_tuple)
            if k <= cnt:
                result.append(ch)
                break
            else:
                k -= cnt
                counter[ch] += 1
        else:
            return ""  # 无法构造出合法解

    return ''.join(result)

class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        n = len(s)
        counter = Counter(s)
        
        # 找到出现次数为奇数的字符
        odd_char = ''
        for ch, count in counter.items():
            if count % 2 == 1:
                odd_char = ch
                counter[ch] -= 1
                break
        
        # 构造第 k 小的回文串
        half = []
        for ch in sorted(counter.keys()):
            half.extend([ch] * (counter[ch] // 2))
        
        kth_half = kth_smallest_permutation(half, k)
        if len(half) > 0 and kth_half == "":
            return ""
        return kth_half + odd_char + kth_half[::-1]