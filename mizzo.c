/** 
 * PAGETABLE.C
 * 
 * Gabriel Barrera
 * Tara Vu
 * Professor Roch
 * CS 570
 * Due Date: Thursday 04/16/2019
 */

#include "mizzo.h"

/** 
 * NUMCHECK
 * 
 * Verifies if string is a number
 */
bool numcheck(char ** argv, int i){
    int j;
    bool valid = true;
    for (j=0;j<strlen(argv[i]);j++){
        if (!isdigit(argv[i][j]))
        valid = false;
    }
    return valid;
}

/**
 * MAIN
 * 
 * Executes pagetable with parameters.
 */
int main(int argc, char ** argv){
    int i = 0; // Argument counter
    int j = 0; // lvlBits counter
    int ethl = 0; // Ethels milliseconds
    int lucy = 0; // Lucys milliseconds
    int fval = 0; // Frog Bite milliseconds
    int eval = 0; // Escargo Sucker milliseconds
    bool ethlf = false; // Memory set flag
    bool lucyf = false; // Export file flag
    bool fflag = false; // Physical address location
    bool eflag = false;
    
    // Args 1 to 5 contain the max amount of flag args 
    for(i=0; i < argc; i++){
        // -E FLAG
        if (strcmp(argv[i],"-E") == 0){
            if (argv[i+1]!=NULL){
                if (numcheck(argv,i+1)){
                    ethl = atoi(argv[i+1]);
                    ethlf = true;
                    i++;
                }
                else printf("** ERR: Non-integer, -E flag using NO DELAY\n");
            }

            else printf("** ERR: No arg, -E flag using NO DELAY\n");
        }

        // -L FLAG
        if (strcmp(argv[i],"-L") == 0){
            if (argv[i+1]!=NULL){
                if (numcheck(argv,i+1)){
                    lucy = atoi(argv[i+1]);
                    lucyf = true;
                    i++;
                }
                else printf("** ERR: Non-integer, -L flag using NO DELAY\n");
            }

            else printf("** No arg, -L flag using NO DELAY\n");
        }

        // -f FLAG
        if (strcmp(argv[i],"-f") == 0){
            if (argv[i+1]!=NULL){
                if (numcheck(argv,i+1)){
                    fval = atoi(argv[i+1]);
                    fflag = true;
                    i++;
                }
                else printf("** ERR: Non-integer, -f flag using NO DELAY\n");
            }

            else printf("** ERR: No arg, -f flag using NO DELAY\n");
        }

        // -e FLAG
        if (strcmp(argv[i],"-e") == 0){
            if (argv[i+1]!=NULL){
                if (numcheck(argv,i+1)){
                    eval = atoi(argv[i+1]);
                    eflag = true;
                    i++;
                }
                else printf("** ERR: Non-integer, -e flag using NO DELAY\n");
            }

            else printf("** ERR: No arg, -e flag using NO DELAY\n");
        }
    }

    printf("\nETHEL: %d ms\n", ethl);
    printf("LUCY: %d ms\n", lucy);
    printf("FROG: %d ms\n", fval);
    printf("ESCARGO: %d ms\n", eval);

    return 0;
}