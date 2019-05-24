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
    def get_rank(nums, possible):
        cnt = j = 0
        for i, v in enumerate(nums):
            while j < len(nums) and nums[j] - v <= possible:
                j += 1
            cnt += j - i - 1
        return cnt
