/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   
    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;
			board[i][j].numTokens = 0;
        }
    }
}
    
    
int initialize_players(player players[]){
    
    //YOU WILL NEED TO IMPLEMENT THIS FUNCTION IN THIS LAB
    printf("\nEnter the number of players: ");
    int num;
    scanf("%d", &num);
    
    for(int i=0; i<num; i++){
        printf("Enter name of player %d\n", i+1);
		scanf("%s", players[i].name);
		players[i].col = i;
    }
   
    return num;
}
    
     

