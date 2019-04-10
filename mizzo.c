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
int main(int argc, char * argv[]){
    int opt; 
    int ethl = 0;
    int lucy = 0;
    int fval = 0;
    int eval = 0;  
    // put ':' in the starting of the 
    // string so that program can  
    //distinguish between '?' and ':'  
    while((opt = getopt(argc, argv, ":if:lrx")) != -1)  
    {  
        switch(opt)  
        {  
            case 'E':  
            case 'L':  
            case 'e':  
                printf("option: %c\n", opt);  
                break;  
            case 'f':  
                printf("filename: %s\n", optarg);  
                break;  
            case ':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    }  
      
    // optind is for the extra arguments 
    // which are not parsed 
    for(; optind < argc; optind++){      
        printf("extra arguments: %s\n", argv[optind]);  
    }

    return 0;
}