class TicTacToe:
    X = 1
    O = 2

    def __init__(self, dimension):
        self.dim = dimension
        self.board = []
        for i in range(0, dimension):
            self.board.append([0]*dimension)
        self.run()

    def print_board(self):
        for i in self.board:
            for j in i:
                mark = "- "
                if j == TicTacToe.X:
                    mark = "X "
                elif j == TicTacToe.O:
                    mark = "O "
                print(mark, end='')
            print()

    def place_move(self, player, i, j):
        # if move is invalid
        if player != TicTacToe.X and player != TicTacToe.O:
            return False
        # if i or j values are invalid
        if i >= self.dim or j >= self.dim or i < 0 or j < 0:
            return False
        # if there is a X or O already placed
        if self.board[i][j] != 0:
            return False
        # place move
        self.board[i][j] = player
        return True

    def check_full(self):
        """Checks is the board is full or not"""
        for i in self.board:
            for j in i:
                if j == 0:
                    return False
        return True

    def check_terminal(self, player):
        """Returns True if there are 3 consecutive X's or O's"""
        # check horizontal
        for i in self.board:
            sum = 0
            for j in i:
                if j == player:
                    sum += player
            if sum == (self.dim * player):
                return True

        # check vertical
        for j in range(0, self.dim):
            sum = 0
            for i in range(0, self.dim):
                if self.board[i][j] == player:
                    sum += player
            if sum == (self.dim * player):
                return True

        # check left diagonal
        sum = 0
        for i in range(0, self.dim):
            if self.board[i][i] == player:
                sum += player
        if sum == (self.dim * player):
            return True

        # check right diagonal
        sum = 0
        for i in range(0, self.dim):
            if self.board[i][self.dim-i-1] == player:
                sum += player
        if sum == (self.dim * player):
            return True

        # no winner
        return False

    def run(self):
        print("Game started")
        player = 1
        winner = 0
        while True:
            self.print_board()
            if player == TicTacToe.X:
                print("X's turn")
            else:
                print("O's turn")
            # read move coordinates
            i = int(input("Enter i value: "))
            j = int(input("Enter j value: "))
            # place the move
            valid = self.place_move(player, i, j)
            while not valid:
                print("invalid i or j value, try again")
                self.print_board()
                i = int(input("Enter i value: "))
                j = int(input("Enter j value: "))
                valid = self.place_move(player, i, j)
            if self.check_full():
                break
            if self.check_terminal(player):
                winner = player
                break
            # set next player
            if player % 2 == 1:
                player = TicTacToe.O
            else:
                player = TicTacToe.X

        self.print_board()
        if winner == 0:
            print("Draw!")
        elif winner == TicTacToe.X:
            print("X won!")
        else:
            print("O won!")


if __name__ == '__main__':
    while True:
        dim = int(input("Enter board dimension: "))
        TicTacToe(dim)
        again = input("Enter q to quit, anything else to play again: ")
        if again == "q":
            break
    print("goodbye...")
