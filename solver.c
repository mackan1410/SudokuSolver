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
        if(i == position) continue;
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
    new_board->cells = calloc(NUM_CELLS, sizeof(int));
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
    if(index == NUM_CELLS) return true;
    if(board->cells[index]) return solve_board(board, index + 1);
    
    for(int i = 1; i <= NUM_POSSIBLE_VALUES; i++){
        if(!valid_move(board, index, i)) continue;
        
        board->cells[index] = i;
        if(solve_board(board, index + 1)) return true;
    }
    
    board->cells[index] = 0;
    
    return false;
}


bool solve(board_t* board){
    return solve_board(board, 0);
}

void print_board(board_t* board){
    printf("\n");
    for(int i = 0; i < NUM_CELLS; i++){
        printf("%d  ", board->cells[i]);
        if((i+1) % NUM_COLS == 0) printf("\n");
    }
}