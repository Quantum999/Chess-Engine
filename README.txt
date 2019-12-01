This is a simple implementation of a chess engine using graphs which stores the information about the positions and the possible movements of
all the pieces that the computer can play against a player.
The inputs for the movement should be given by the player in the fromat given in example:	7b5b
To run the program, run 'make' command on linux when in the folder.

'arr' contains the matrix, 'board' contains the chess board.

functions:

void initmatrix() - initializes the elements of adjacency matrix to -1.

void initboard() - initializes the chess board.

int onboard(int, int) - checks if the given position is on the board or not.

int valid(int, int) - validates the position according to the color provided to it.

void pawn(int, int) - checks all possible moves of the given pawn and includes it in the graph.

void rook(int, int) - checks all possible moves of the given rook and includes it in the graph.

void night(int, int) - check all possible moves of the given knight and includes it in the graph.

void bishop(int, int) - checks all possible moves of the given bishop and includes it in the graph.

void queen(int, int) - checks all possible moves of the given queen and includes it in the graph.

void king(int, int) - checks all possible moves of the given king and includes it inthe graph.

void creategraph() - creates graph for the intitial board.

void patanahi() - check the given piece and applies it's corresponding function for the graph.

void correctgraph() - corrects the graph after a white piece has been moved.

void display() - displays the chess board.

int player() - function for the player's move and returns if the position was valid and if the move by the player killed the white king or not.

int computer() - functin for the computer's move, searches the graph for best move, plays it and returns if it kills black king or not.

void game() - responsible for running player and computer's turn alternatively and check if any color wins.

void clrscr() - clears the screen after every move.

