package main

import "fmt"

// combine generates a cartesian product of list A and B 
func combine(A, B []string) []string {
	combined := make([]string, 0)

	for _, a := range A {
		for _, b := range B {
			combined = append(combined, a+b)
		}
	}

	return combined
}

func enumerateTrees(n int) []string {
	if n == 0 {
		return []string{""}
	}

	if n == 1 {
		return []string{"(.)"}
	}

	combos := make([]string, 0)

	for i := 0; i < n; i++ {
		// left subtree
		combo := []string{"("}
		left := enumerateTrees(n - i - 1)
		combo = combine(combo, left)

		combo = combine(combo, []string{"."})
	
		// right subtree
		right := enumerateTrees(i)
		combo = combine(combo, right)
		combo = combine(combo, []string{")"})

		for _, c := range combo {
			combos = append(combos, c)
		}
	}

	return combos
}

func main() {
	for {
		var n int
		fmt.Print("enter number of nodes, -1 to quit: ")
		fmt.Scanf("%d", &n)
		if n < 0 {
			break
		}

		trees := enumerateTrees(n)
		for _, t := range trees {
			fmt.Println(t)
		}
	}
}
