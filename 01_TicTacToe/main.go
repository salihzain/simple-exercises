package main

import (
	"fmt"
)

func printBoard(board [3][3]int) {
	fmt.Println("-----------")
	fmt.Print("  ")
	for j := 0; j < len(board); j++ {
		fmt.Print(j, " ")
	}
	fmt.Println()
	for i := 0; i < len(board); i++ {
		fmt.Print(i, " ")
		for j := 0; j < len(board); j++ {
			if board[i][j] == 1 {
				fmt.Print("X ")
			} else if board[i][j] == 2 {
				fmt.Print("O ")
			} else {
				fmt.Print("- ")
			}
		}
		fmt.Println()
	}
	fmt.Println("-----------")
}

func isTerminal(board [3][3]int) bool {
	if checkX(board) {
		return true
	}
	if checkO(board) {
		return true
	}
	if checkFull(board) {
		return true
	}
	return false
}

func checkWinner(board [3][3]int) int {
	if checkX(board) {
		return 1
	} else if checkO(board) {
		return 2
	}
	return 0
}

func checkX(board [3][3]int) bool {
	if checkHoriz(board, 1) {
		return true
	}
	if checkVert(board, 1) {
		return true
	}
	if checkDiagonal(board, 1) {
		return true
	}
	return false
}

func checkO(board [3][3]int) bool {
	if checkHoriz(board, 2) {
		return true
	}
	if checkVert(board, 2) {
		return true
	}
	if checkDiagonal(board, 2) {
		return true
	}
	return false
}

func checkFull(board [3][3]int) bool {
	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board); j++ {
			if board[i][j] == 0 {
				return false
			}
		}
	}
	return true
}

func checkHoriz(board [3][3]int, player int) bool {
	for i := 0; i < len(board); i++ {
		sum := 0
		for j := 0; j < len(board); j++ {
			if board[i][j] == player {
				sum += player
			}
		}
		if sum == (len(board) * player) {
			return true
		}
	}
	return false
}

func checkVert(board [3][3]int, player int) bool {
	//left
	sum := 0
	for i := 0; i < len(board); i++ {
		if board[i][i] == player {
			sum += player
		}
	}
	if sum == (len(board) * player) {
		return true
	}

	sum = 0
	for i := 0; i < len(board); i++ {
		if board[i][len(board)-i-1] == player {
			sum += player
		}
	}
	if sum == (len(board) * player) {
		return true
	}

	return false
}

func checkDiagonal(board [3][3]int, player int) bool {
	for j := 0; j < len(board); j++ {
		sum := 0
		for i := 0; i < len(board); i++ {
			if board[i][j] == player {
				sum += player
			}
		}
		if sum == (len(board) * player) {
			return true
		}
	}
	return false
}

func placeX(board [3][3]int, i, j int) [3][3]int {
	for !validateLoc(board, i, j) {
		i, j = enterNewLoc()
	}
	board[i][j] = 1
	return board
}

func placeO(board [3][3]int, i, j int) [3][3]int {
	for !validateLoc(board, i, j) {
		i, j = enterNewLoc()
	}
	board[i][j] = 2
	return board
}

func validateLoc(board [3][3]int, i, j int) bool {
	if i >= len(board) || j >= len(board) || i < 0 || j < 0 {
		return false
	}
	if board[i][j] == 0 {
		return true
	}
	return false
}

func enterNewLoc() (int, int) {
	var i, j int
	fmt.Println("Invalid location, enter new i")
	fmt.Scanf("%d", &i)
	fmt.Println("enter new j")
	fmt.Scanf("%d", &j)
	return i, j
}

func main() {
	var board [3][3]int
	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board); j++ {
			board[i][j] = 0
		}
	}
	printBoard(board)

	var i, j int
	println(i)
	player := 1
	for !isTerminal(board) {
		if player%2 != 0 {
			fmt.Println("x's turn")
		} else {
			fmt.Println("o's turn")
		}
		fmt.Println("enter i")
		fmt.Scanf("%d", &i)
		fmt.Println("enter j")
		fmt.Scanf("%d", &j)
		if player%2 != 0 {
			board = placeX(board, i, j)
		} else {
			board = placeO(board, i, j)
		}
		player++
		printBoard(board)
	}
	winner := checkWinner(board)
	if winner == 1 {
		fmt.Println("X won!")
	} else if winner == 2 {
		fmt.Println("O won")
	} else {
		fmt.Println("It's a draw!!")
	}
}
