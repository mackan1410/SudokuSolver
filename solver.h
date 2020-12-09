#include <stdbool.h>

typedef struct board board_t;

board_t* create_empty_board();

board_t* create_board(int cells[81]);

void destroy_board(board_t* board);

bool solve(board_t* board);

void print_board(board_t* board);