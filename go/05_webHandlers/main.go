package main

import (
	"fmt"
	"log"
	"net/http"
	"strconv"
)

func rootHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/html; charset=utf-8")
	fmt.Fprintln(w, "<h2>To use the dumb calculator API, follow the examples below</h2>")
	fmt.Fprintln(w, "<h4>Add x+y: /calc?op=add&x=1&y=2</h4>")
	fmt.Fprintln(w, "<h4>Substract x-y: /calc?op=sub&x=1&y=2</h4>")
	fmt.Fprintln(w, "<h4>Multiply x*y: /calc?op=mult&x=1&y=2</h4>")
	fmt.Fprintln(w, "<h4>Divide x/y: /calc?op=div&x=1&y=2</h4>")
}

func calcHandler(w http.ResponseWriter, r *http.Request) {
	op, ok := r.URL.Query()["op"]
	if !validOp(op, ok) {
		fmt.Fprintln(w, "You have to specify a valid operator. For example: ?op=add")
		fmt.Fprintln(w, "Available operators: add, sub, mult, div")
		return
	}
	x, ok := r.URL.Query()["x"]
	if !validX(x, ok) {
		fmt.Fprintln(w, "Please enter a number for x. For example: ?x=23.14")
		return
	}

	y, ok := r.URL.Query()["y"]
	if !validY(y, ok) {
		fmt.Fprintln(w, "Please enter a number for y. For example: ?y=24.14")
		return
	}

	res := calc(op[0], x[0], y[0])
	fmt.Fprintf(w, "op: %s, x=%s, y=%s\nResult=%f", op[0], x[0], y[0], res)
}

func validOp(op []string, ok bool) bool {
	if !ok || len(op[0]) < 1 {
		return false
	}
	return (op[0] == "add" || op[0] == "sub" || op[0] == "mult" || op[0] == "div")
}

func validX(x []string, ok bool) bool {
	if _, err := strconv.ParseFloat(x[0], 64); err != nil {
		return false
	}
	return !(!ok || len(x[0]) < 1)
}

func validY(y []string, ok bool) bool {
	if _, err := strconv.ParseFloat(y[0], 64); err != nil {
		return false
	}
	return !(!ok || len(y[0]) < 1)
}

func calc(op string, x string, y string) float64 {
	xF, err := strconv.ParseFloat(x, 64)
	checkErr(err)
	yF, err := strconv.ParseFloat(y, 64)
	checkErr(err)

	switch op {
	case "add":
		return xF + yF
	case "sub":
		return xF - yF
	case "mult":
		return xF * yF
	case "div":
		return xF / yF
	default:
		return 0
	}
}
func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}

func main() {
	http.HandleFunc("/", rootHandler)
	http.HandleFunc("/calc", calcHandler)
	log.Fatal(http.ListenAndServe(":8000", nil))
}
