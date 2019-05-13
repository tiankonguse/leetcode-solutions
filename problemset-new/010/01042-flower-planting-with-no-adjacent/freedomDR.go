package main

import "fmt"

func gardenNoAdj(N int, paths [][]int) []int {
	ans := make([]int, N)
	edge := make([][]int, N)
	for i := 0; i < len(paths); i++ {
		x := paths[i][0] - 1
		y := paths[i][1] - 1
		edge[x] = append(edge[x], y)
		edge[y] = append(edge[y], x)
	}
	for i := 0; i < N; i++ {
		used := [5]bool{}
		for _, v := range edge[i] {
			used[ans[v]] = true
		}
		for v := 1; v <= 4; v++ {
			if used[v] == false {
				ans[i] = v
			}
		}
	}
	return ans
}

func main() {
	fmt.Println("hello")
}
