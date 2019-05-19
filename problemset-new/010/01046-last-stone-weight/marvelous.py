import heapq
from typing import List
import operator


class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        c1 = list(map(operator.neg, stones))
        heapq.heapify(c1)

        while len(c1) >= 2:
            first, second = heapq.heappop(c1), heapq.heappop(c1)
            if first != second:
                heapq.heappush(c1, first - second)
        return -c1[0] if c1 else 0

