package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

func checkError(e error) {
	if e != nil {
		panic(e)
	}
}
func main() {
	data, err := ioutil.ReadFile("ds.txt")
	checkError(err)

	dataSlice := strings.Split(string(data), "\n")
	for i := 0; i < len(dataSlice); i++ {
		temp := strings.Split(dataSlice[i], ",")
		if len(temp) < 3 {
			break
		}
		x1, _ := strconv.ParseFloat(temp[0], 64)
		x2, _ := strconv.ParseFloat(temp[1], 64)
		y, _ := strconv.ParseInt(temp[2], 10, 32)
		fmt.Println(x1, x2, y)
	}

	// straight forward way
	dataW := []byte(data)
	err = ioutil.WriteFile("ds_new.txt", dataW, 0644)
	checkError(err)
}
