/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <time.h>
#include "game_init.h"
#include <stdio.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
 
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints a horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
 
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    
	int minNumOfTokens = 0;
    int selectedSquare = 0;
	
	for(int i=0; i<4; i++){
		for(int j=0; j<numPlayers; j++){
			printf("%s please select a square\n", players[j].name);
			scanf("%d", &selectedSquare);
			
			if(minNumOfTokens == 0){
				if(board[selectedSquare][0].numTokens > minNumOfTokens){
					printf("\nInvalid square. Cannot place a token until all rows are filled\n");
					j--;//make this player stay in the loop until they pick a valid square
				}
				else{
					board[selectedSquare][0].stack = push(players[j].col, board[selectedSquare][0].stack,  &board[selectedSquare][0].numTokens);
					print_board(board);
					if(((numPlayers * i) + j + 1)%NUM_ROWS == 0)
						minNumOfTokens++;
				}
			}
			else if(minNumOfTokens > 0){
				if(board[selectedSquare][0].numTokens > minNumOfTokens){
					printf("\n\nInvalid square. Cannot place a token until all rows are filled\n\n");
					j--;//make this player stay in the loop until they pick a valid square
				}
				else if((board[selectedSquare][0].stack->col) == players[j].col){
					printf("\n\nInvalid square. Cannot place token on top of token of same colour\n\n");
					j--;
				}
				else{
					board[selectedSquare][0].stack = push(players[j].col, board[selectedSquare][0].stack,  &board[selectedSquare][0].numTokens);
					print_board(board);
					if(((numPlayers * i) + j + 1)%NUM_ROWS == 0)
						minNumOfTokens++;
				}
			}
		}
	}
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    //TO BE IMPLEMENTED
}

