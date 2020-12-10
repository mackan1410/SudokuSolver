#include "../solver.h"
#include <stdbool.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

int init_suite(void){
    return 0;
}

int clean_suite(void){
    return 0;
}

void test_solve(){
    
    int cells[81] = {
        8, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 3, 6, 0, 0, 0, 0, 0,
        0, 7, 0, 0, 9, 0, 2, 0, 0,
        0, 5, 0, 0, 0, 7, 0, 0, 0,
        0, 0, 0, 0, 4, 5, 7, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 3, 0,
        0, 0, 1, 0, 0, 0, 0, 6, 8,
        0, 0, 8, 5, 0, 0, 0, 1, 0,
        0, 9, 0, 0, 0, 0, 4, 0, 0 
    };
    
    int cells2[81] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    
    int cells3[81] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        9, 8, 7, 6, 5, 4, 3, 2, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    
    
    
    board_t* board = create_board(cells);
    board_t* board2 = create_board(cells2);
    //board_t* board3 = create_board(cells3);
    
    
    CU_ASSERT(solve(board));
    CU_ASSERT(solve(board2));
    //CU_ASSERT(!solve(board3));
    
    destroy_board(board);
    destroy_board(board2);
    //destroy_board(board3);
}

void test_create_board(){}



int main()
{
    CU_pSuite test_suite1 = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    test_suite1 = CU_add_suite("Solver test suite", init_suite, clean_suite);
    if (NULL == test_suite1){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(test_suite1, "test solving", test_solve)) ||
        (NULL == CU_add_test(test_suite1, "test createe board", test_create_board)) 
        
    ){
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}