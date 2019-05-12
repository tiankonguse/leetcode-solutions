# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def bstToGst(self, root: TreeNode) -> TreeNode:
        def postorder(rt, suffix_sum):
            if not rt:
                return suffix_sum
            suffix_sum = rt.val = rt.val + postorder(rt.right, suffix_sum)
            return postorder(rt.left, suffix_sum)
        postorder(root, 0)
        return root
