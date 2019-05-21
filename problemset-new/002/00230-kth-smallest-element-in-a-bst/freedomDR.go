package main

import "fmt"

var sums int

func kthSmallest(root *TreeNode, k int) int {
	sums = 0
	return slove(root, k)
}
func slove(root *TreeNode, k int) int {
	if root == nil || sums > k {
		return 1
	} else {
		l := slove(root.Left, k)
		sums++
		if sums == k {
			return root.Val
		}
		r := slove(root.Right, k)
		return l * r
	}
}
func main() {
	fmt.Println("vim-go")
}
