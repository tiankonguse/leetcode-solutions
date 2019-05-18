class Solution:
    def hIndex(self, citations: List[int]) -> int:
        h = len(citations)
        for i, val in enumerate(reversed(sorted(citations)), 1):
            if i > val:
                h = i - 1
                break
        return h
