package main

import (
	"fmt"
	"time"
)

var stopSignal = make(chan bool)

type scheduler struct {
	taskTable map[time.Time][]task
	stop      bool
}

func newScheduler() scheduler {
	s := scheduler{
		taskTable: make(map[time.Time][]task),
		stop:      false,
	}
	return s
}

func (s *scheduler) appendTask(t task) {
	s.taskTable[t.getTime().Round(time.Second)] = append(s.taskTable[t.getTime().Round(time.Second)], t)
}

func (s *scheduler) start() {
	for !s.stop {
		fmt.Print(time.Now().Round(time.Second), " ")
		tasks, ok := s.taskTable[time.Now().Round(time.Second)]
		if ok {
			for _, task := range tasks {
				task.doTask()
			}
		}
		time.Sleep(time.Second)
		fmt.Println("")
	}
	stopSignal <- true
}

func (s *scheduler) stopIt() {
	s.stop = true
}

type task interface {
	getTime() time.Time
	doTask()
}

type printTask struct {
	time time.Time
	task func()
}

func (pt *printTask) getTime() time.Time {
	return pt.time
}

func (pt *printTask) doTask() {
	pt.task()
}

func main() {
	f := func() {
		fmt.Println("hello world")
	}
	ptTime := time.Now().Add(time.Second * 3)
	pt := &printTask{
		time: ptTime,
		task: f,
	}
	s := newScheduler()
	s.appendTask(pt)
	go s.start()
	time.Sleep(time.Duration(time.Second * 6))
	s.stopIt()
	<-stopSignal
}
