/* File: solve.h */
#include <stdio.h>                                                                                                               /* Header file for standard I/O library */
#include <stdlib.h>                                                                                                                    /* Header file for malloc function*/


/* #define REC */                                                                                                                 /* gcc -DREC -o elevatorrec elevator.c */
/* #define MEM */                                                                                                                 /* gcc -DMEM -o elevatormem elevator.c */
/* #define DP */                                                                                                                    /* gcc -DDP -o elevatordp elevator.c */
/* #define BF */                                                                                                                    /* gcc -DBF -o elevatorbf elevator.c */

#define MAX_INT     ( ~ ( 1 << ( 8 * sizeof(int) - 1 ) ) )                                        /* The biggest possitive signed integer in order to represent infinity */

#ifndef   FALSE
  #define FALSE 0
#endif

#ifndef   TRUE
  #define TRUE (!FALSE)
#endif

int solve(int nrid, int nst, int *dests);                                                               /* This function computes the cost of the best possible solution */
