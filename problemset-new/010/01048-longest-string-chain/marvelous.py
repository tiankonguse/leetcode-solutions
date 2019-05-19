from collections import defaultdict
from typing import List


class Solution:
    def longestStrChain(self, words: List[str]) -> int:
        n = len(words)
        dp = [1] * n
        size2idx = defaultdict(list)
        uniq = list(set(words))
        uniq.sort(key=len)
        for i, word in enumerate(uniq):
            k = len(word)
            for idx in size2idx.get(k - 1, []):
                if self.is_chain(uniq[idx], word):
                    dp[i] = max(dp[i], dp[idx] + 1)
            size2idx[k].append(i)

        return max(dp)

    @classmethod
    def is_chain(cls, src, dst):
        prefix = 0
        for s, d in zip(src, dst):
            if s != d:
                break
            prefix += 1

        suffix = len(src) - 1
        while suffix >= 0:
            if src[suffix] != dst[suffix + 1]:
                break
            suffix -= 1

        return prefix > suffix

