class Solution:
    def removeDuplicates(self, S: str) -> str:
        stack = []
        for char in S:
            if not stack or stack[-1] != char:
                stack.append(char)
            else:
                stack.pop()
        return ''.join(stack)
