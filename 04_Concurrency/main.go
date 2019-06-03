package main

import "fmt"

func sum(s []int, c chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	c <- sum
}

func main() {
	values := []int{1, 2, 3, 4, 5, 6}
	c := make(chan int)
	go sum(values[:len(values)/2], c)
	go sum(values[len(values)/2:], c)
	x, y := <-c, <-c
	fmt.Println(x, y)

}
