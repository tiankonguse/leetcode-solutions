package main

import "fmt"
import "sort"

func findRadius(houses []int, heaters []int) int {
	pos := 0
	ans := 0
	sort.Sort(sort.IntSlice(houses))
	sort.Sort(sort.IntSlice(heaters))
	fmt.Println(houses)
	fmt.Println(heaters)
	for i := range houses {
		for ; pos < len(heaters); pos++ {
			if houses[i] < heaters[pos] {
				break
			}
		}
		if pos != 0 {
			pos--
		}
		t1 := houses[i] - heaters[pos]
		t1 = int(math.Abs(float64(t1)))
		t2 := int(1e9)
		if pos != len(heaters)-1 {
			t2 = houses[i] - heaters[pos+1]
			t2 = int(math.Abs(float64(t2)))
		}
		ans = int(math.Max(float64(ans), math.Min(float64(t1), float64(t2))))
	}
	return ans
}
func main() {
	fmt.Println("vim-go")
}
