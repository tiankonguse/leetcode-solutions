package main

import "fmt"

func searchMatrix(matrix [][]int, target int) bool {
	if len(matrix) == 0 {
		return false
	}
	r, l := len(matrix), len(matrix[0])
	lo, hi := 0, r*l
	//fmt.Println(lo, hi)
	for lo < hi {
		mid := lo + (hi-lo)/2
		if matrix[mid/l][mid%l] < target {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	if lo == r*l || matrix[lo/l][lo%l] != target {
		return false
	} else {
		return true
	}
}
func main() {
	fmt.Println("vim-go")
}
