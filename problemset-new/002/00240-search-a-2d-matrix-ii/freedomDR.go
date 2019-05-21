package main

import "fmt"

func searchMatrix(matrix [][]int, target int) bool {
	if len(matrix) == 0 {
		return false
	}
	row, column := len(matrix), len(matrix[0])
	i, j := row-1, 0
	for i >= 0 && j < column {
		if matrix[i][j] == target {
			return true
		} else if matrix[i][j] < target {
			j++
		} else {
			i--
		}
	}
	return false
}
func main() {
	fmt.Println("vim-go")
}
