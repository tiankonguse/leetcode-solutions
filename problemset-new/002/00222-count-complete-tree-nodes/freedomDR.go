package main

import "fmt"

func getDepth(root *TreeNode) int {
	depth := 0
	for root != nil {
		depth++
		root = root.Left
	}
	return depth
}

func countNodes(root *TreeNode) int {
	if root == nil {
		return 0
	} else {
		ld := getDepth(root.Left)
		rd := getDepth(root.Right)
		if ld == rd {
			return 1 + int(uint(1)<<uint(ld)) - 1 + countNodes(root.Right)
		} else {
			return 1 + int(uint(1)<<uint(rd)) - 1 + countNodes(root.Left)
		}
	}
}
func main() {
	fmt.Println("vim-go")
}
