/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]);


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);



/* 
 *  * Manages the logic of the game
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players 
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);

struct token *push(int colour, struct token *top, int *tokensOnSquare){
	struct token *curr = top;
	top = malloc(sizeof(token));
	top->col = colour;
	top->next = curr;
	*tokensOnSquare = *tokensOnSquare+1;
	return top;
	
}

struct token *pop(struct token *top, int *tokensOnSquare){
	struct token *curr = top;
	if(curr != NULL){
		top = curr->next;
		free(curr);
		*tokensOnSquare = *tokensOnSquare - 1;
	}
	return top;
}

struct token *finalpop(struct token *top, int *tokensOnSquare, int *finalColTok){
	struct token *curr = top;
	if(curr != NULL){
		top = curr->next;
		free(curr);
		*tokensOnSquare = *tokensOnSquare - 1;
		*finalColTok = *finalColTok + 1;
	}
	return top;
}