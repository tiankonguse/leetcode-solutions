class Solution:
    def lastStoneWeightII(self, stones: List[int]) -> int:
        dp = {0}
        for elem in stones:
            new = set()
            for item in dp:
                new.update({item + elem, item - elem})
            dp = new
        return min(dp, key=abs)

