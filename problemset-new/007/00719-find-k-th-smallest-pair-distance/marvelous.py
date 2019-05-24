class Solution:
    def smallestDistancePair(self, nums: List[int], k: int) -> int:
        order = sorted(nums)
        
        low, high = 0, order[-1] - order[0]
        while low < high:
            mid = (low + high) >> 1
            rank = self.get_rank(order, mid)
            if rank >= k:
                high = mid
            else:
                low = mid + 1
        return low
    
    @staticmethod
    def get_rank(order, mid):
        n = len(order)
        rank = 0
        for i in range(n - 1):
            index = bisect.bisect_right(order, order[i] + mid, i + 1)
            rank += index - i - 1
        return rank
