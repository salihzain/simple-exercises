package linkedlist

import (
	"reflect"
)

type List interface {
	Add(e interface{})
	Clear()
	Contains(e interface{}) bool
	Equals(that List) bool
	Get(index int) interface{}
	IndexOf(e interface{}) int
	IsEmpty() bool
	Remove(index int) interface{}
	Size() int
	ToArray() []interface{}
}

type LinkedList struct {
	size int
	head *node
}

type node struct {
	data interface{}
	next *node
}

// creates and return a new empty LinkedList
func NewLinkedList() *LinkedList {
	return &LinkedList{0, nil}
}

func (l *LinkedList) Add(e interface{}) {
	if l.head == nil {
		l.head = &node{e, nil}
	} else {
		var nd *node
		for nd = l.head; nd.next != nil; nd = nd.next {
		}
		nd.next = &node{e, nil}
	}
	l.size++
}

func (l *LinkedList) Clear() {
	l.head = nil
	l.size = 0
}

func (l *LinkedList) Contains(e interface{}) bool {
	if l.size == 0 {
		return false
	}
	for nd := l.head; ; nd = nd.next {
		if nd.data == e {
			return true
		}
		if nd.next == nil {
			break
		}
	}
	return false
}

func (l *LinkedList) Equals(that List) bool {
	if reflect.TypeOf(l) != reflect.TypeOf(that) {
		return false
	}

	for i := 0; i < l.size; i++ {
		if l.Get(i) != that.Get(i) {
			return false
		}
	}
	return true
}

func (l *LinkedList) Get(index int) interface{} {
	if index < 0 || index >= l.size {
		return nil
	}
	nd := l.head
	for i := 0; i < index; nd = nd.next {
		i++
	}
	return nd.data
}

func (l *LinkedList) IndexOf(e interface{}) int {
	if !l.Contains(e) {
		return -1
	}
	i := 0
	for nd := l.head; nd.data != e; nd = nd.next {
		i++
	}
	return i
}

func (l *LinkedList) IsEmpty() bool {
	return l.size == 0
}

func (l *LinkedList) Remove(index int) interface{} {
	if index < 0 || index >= l.size {
		return nil
	}

	if index == 0 {
		temp := l.head
		l.head = l.head.next
		return temp
	}

	var nd *node
	i := 0
	for nd = l.head; i < index-1; nd = nd.next {
		i++
	}
	temp := nd.next
	nd.next = nd.next.next
	return temp
}

func (l *LinkedList) Size() int {
	return l.size
}

func (l *LinkedList) ToArray() []interface{} {
	list := make([]interface{}, 0)
	if l.head != nil {
		for nd := l.head; nd != nil; nd = nd.next {
			list = append(list, nd.data)
		}
	}
	return list
}
