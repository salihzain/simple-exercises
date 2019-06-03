package main

import (
	"fmt"

	linkedlist "github.com/sigmazain/go-exercises/03_LinkedList/LinkedList"
)

func main() {
	l := linkedlist.NewLinkedList()
	var l2 linkedlist.List = linkedlist.NewLinkedList()

	l2.Add("1")
	fmt.Println(l2.ToArray())
	l.Add("1")
	l.Add("2")
	l.Add("3")

	list := l.ToArray()
	fmt.Println(list)
	fmt.Println(l.Get(1))

	fmt.Println(l.Remove(0))
	fmt.Println(l.ToArray())

	var x linkedlist.List
	x = l
	fmt.Println(x.ToArray())
}
