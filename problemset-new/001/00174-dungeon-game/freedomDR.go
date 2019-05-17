package main

import "fmt"

// 卧槽，做完这道题我的血量已经成为负值了(打死都想不到沿着相反的方向来)
func max(v1, v2 int) int {
	if v1 > v2 {
		return v1
	} else {
		return v2
	}
}
func min(v1, v2 int) int {
	if v1 > v2 {
		return v2
	} else {
		return v1
	}
}

func calculateMinimumHP(dungeon [][]int) int {
	row, column := len(dungeon), len(dungeon[0])
	cost := make([][]int, row+1)
	for i := range cost {
		cost[i] = make([]int, column+1)
	}
	for i := 0; i <= row; i++ {
		cost[i][column] = int(1e9)
	}
	for i := 0; i <= column; i++ {
		cost[row][i] = int(1e9)
	}
	for i := row - 1; i >= 0; i-- {
		for j := column - 1; j >= 0; j-- {
			if i == row-1 && j == column-1 {
				if dungeon[i][j] > 0 {
					cost[i][j] = 1
				} else {
					cost[i][j] = 1 - dungeon[i][j]
				}
			} else {
				cost[i][j] = max(1, min(cost[i+1][j], cost[i][j+1])-dungeon[i][j])
			}
		}
	}
	return cost[0][0]
}
func main() {
	fmt.Println("vim-go")
}
