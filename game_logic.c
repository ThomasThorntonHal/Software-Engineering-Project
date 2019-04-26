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
	srand(time(NULL));
	int roll, end = 0, found, choice, row, column, UoD, safety, z;
	for(z=0; z<numPlayers; z++)
		players[z].numTokensLastCol = 0;
	while(end != 1){
		for(int j=0; j<numPlayers; j++){
			found = 0;
			roll = rand()%6;
			printf("\n%s roll: %d\n", players[j].name, roll);
			for(int q=0; q<NUM_COLUMNS; q++){
				if(board[roll][q].numTokens != 0)
					found = 1;
			}
			if(found == 1){
				choice = 0;
				printf("\nDo you want to move one of your tokens up or down?\n1 for Yes\n2 for No\n");
				scanf("%d", &choice);
				
				while(choice == 1){
					printf("\n%s enter the coordinates of the token you want to move (x then y): ", players[j].name);
					scanf("%d %d", &column, &row);
					int canPlaMove = 1;
					if(board[row][column].type == OBSTACLE){
						for(int x = 0; x < column; x++){ //check if there are tokens in any square behind the obstacle
							for(int y = 0; y < 6; y++){
								if(board[y][x].stack != NULL)
									canPlaMove = 0;
							}
						}		
					}
					if(canPlaMove == 0){
						printf("\nCannot move that token yet (on an obstacle)");
						choice = 2;
					}
					else if(canPlaMove == 1){
						if((board[row][column].stack == NULL) || (board[row][column].stack->col != players[j].col))
							printf("\nYou don't have a token on that square\n");
						else{
							printf("\nMove (1)UP or (2)DOWN?\n");
							safety = 0;
							while(safety != 1){
								scanf("%d", &UoD);
								if((row == 0 && UoD == 1) || (row == 5 && UoD == 2) || (UoD != 1 && UoD != 2))
									printf("\nInvalid choice\n");
								else
									safety = 1;
							} 
						
							board[row][column].stack = pop(board[row][column].stack, &board[row][column].numTokens);
							if(UoD == 1)
								board[row - 1][column].stack = push(players[j].col, board[row - 1][column].stack, &board[row - 1][column].numTokens);
							else if(UoD == 2)
								board[row + 1][column].stack = push(players[j].col, board[row + 1][column].stack, &board[row + 1][column].numTokens);
							print_board(board);
						
							choice = 2;
						}
					}
				}
				if(choice == 2){
					found = 0;//check for tokens in this row in case someone moved the last token out of this row
					for(int q=0; q<NUM_COLUMNS; q++){
						if(board[roll][q].numTokens != 0)
						found = 1;
					}
					if(found == 1){
						printf("\n%s enter the column of the token you want to move: ", players[j].name);
						do{
							scanf("%d", &column);
							if(board[roll][column].stack == NULL)
								printf("\nNo token on that square\n");
						} while(board[roll][column].stack == NULL);
					
						//check if token can move
						int canPlaMove = 1;
						if(board[roll][column].type == OBSTACLE){
							for(int x = 0; x < column; x++){ //check if there are tokens in any square behind the obstacle
								for(int y = 0; y < 6; y++){
									if(board[y][x].stack != NULL)
										canPlaMove = 0;
								}
							}		
						}
						if(canPlaMove == 0)
							printf("\nToken cannot move yet (stuck in obstacle)\n");
						else{
							board[roll][column + 1].stack = push(board[roll][column].stack->col, board[roll][column + 1].stack, &board[roll][column + 1].numTokens);
							board[roll][column].stack = pop(board[roll][column].stack, &board[roll][column].numTokens);
							print_board(board);
							if(column == 7)
								board[roll][8].stack = finalpop(board[roll][8].stack, &board[roll][8].numTokens, &players[board[roll][8].stack->col].numTokensLastCol);
						}
					}
				}
			}
			else
				printf("\nNo tokens in that row. Next turn.\n");
			for(z=0; z<numPlayers; z++){
				if(players[z].numTokensLastCol > 2){
					printf("\n%s wins", players[z].name);
					end = 1;
				}
			}
		}
	}
	
}

