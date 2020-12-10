#include "solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define NUM_CELLS 81
#define NUM_ROWS 9
#define NUM_COLS 9
#define ROWS_PER_BLOCK 3
#define COLS_PER_BLOCK 3
#define NUM_POSSIBLE_VALUES 9

struct board{
    int* cells;
};

static int col(int a){
    return a % NUM_COLS;
}

static int row(int a){
    return floor(a / NUM_ROWS);
}

static int block(int a){
    return (floor(col(a) / COLS_PER_BLOCK)) + (floor(row(a) / ROWS_PER_BLOCK))*ROWS_PER_BLOCK;
}

static bool same_row(int a, int b){
    return row(a) == row(b);
}

static bool same_col(int a, int b){
    return col(a) == col(b);
}

static bool same_block(int a, int b){
    return block(a) == block(b);
}

static bool valid_move(board_t* board, int position, int value){
    for(int i = 0; i < NUM_CELLS; i++){
        if((same_col(position, i) ||
            same_row(position, i) ||
            same_block(position, i)) &&
            board->cells[i] == value){
            return false;
        }
    }
    return true;
}

board_t* create_empty_board(){
    board_t* new_board = calloc(1, sizeof(board_t));
    new_board->cells = calloc(81, sizeof(int));
    return new_board;
}

board_t* create_board(int* cells){
    board_t* new_board = create_empty_board();
    
    for(int i = 0; i < NUM_CELLS; i++){
        new_board->cells[i] = cells[i];
    }
    
    return new_board;
}


void destroy_board(board_t* board){
    free(board->cells);
    free(board);
}

static bool solve_board(board_t* board, int index){
    if(board->cells[index]){
        if(index + 1 == NUM_CELLS) return true;
        return solve_board(board, index + 1);
    }
    
    int possible_values[NUM_POSSIBLE_VALUES] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
    for(int i = 0; i < NUM_POSSIBLE_VALUES; i++){
        if(!valid_move(board, index, possible_values[i])) continue;
        
        board->cells[index] = possible_values[i];
        if(index + 1 == NUM_CELLS || solve_board(board, index + 1)) return true;
    }
    
    board->cells[index] = 0;
    return false;
}


bool solve(board_t* board){
    return solve_board(board, 0);
}

void print_board(board_t* board){
    for(int i = 0; i < NUM_CELLS; i++){
        printf("%d  ", board->cells[i]);
        if((i+1) % NUM_ROWS == 0) printf("\n");
    }
}