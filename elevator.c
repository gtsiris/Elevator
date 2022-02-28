/* File: main.c */
#include <stdio.h>                                                                                                               /* Header file for standard I/O library */
#include <stdlib.h>                                                                                                                    /* Header file for malloc function*/
#include "solve.h"                                                                                                                     /* Header file for solve function */


int main(void) {
  #if (!defined(REC) && !defined(MEM) && !defined(DP) && !defined(BF))
    printf("Please compile as: \"gcc -DREC -o elevatorrec elevator.c solve.c\" or\n\
                   \"gcc -DMEM -o elevatormem elevator.c solve.c\" or\n\
                   \"gcc -DDP -o elevatordp elevator.c solve.c\"   or\n\
                   \"gcc -DBF -o elevatorbf elevator.c solve.c\"\n");
  #else
    int nrid, nst, *dests, n, cost;                                    /* nrid: number of riders, nst: maximum number of stops, dests: destinations, n: counter for nrid */
    scanf ("%d %d", &nrid, &nst);                                                                        /* Read number of riders and maximum number of stops from input */
    dests = malloc(nrid * sizeof(*dests));                                                                                           /* Allocate memory for destinations */
    if (dests == NULL) {                                                                                 /* In case of unsuccefull memory allocation, finish the program */
      printf("Sorry, a memory problem occurred\n");
      return -1;
    }
    for (n = 0; n < nrid; n++) {
      scanf("%d", dests + n);                                                                                                     /* Read one destination for each rider */
    }
    cost = solve(nrid, nst, dests);                                                                    /* solve function computes the cost of the best possible solution */
    free(dests);
    if (cost == -1) {                                                                               /* If the returned value from solve is -1, there is a memory problem */
      printf("Sorry, a memory problem occurred\n");
      return -1;
    }
    printf("Cost is: %d\n", cost);                                                                                                                     /* Print the cost */
    return 0;
  #endif
}
