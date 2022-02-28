/* File: solve.c */
#include "solve.h"                                                                                                                     /* Header file for solve function */




#ifdef REC


int fw(int a, int b, int nrid, int *dests);                                                             /* This function computes the cost between two consecutive stops */


int M(int i, int j, int nrid, int *dests);                                                                        /* This function recursively computes the minimum cost */


int solve(int nrid, int nst, int *dests) {                                                                                                                  /* Recursive */
  int n, nfl = 0, i, cost, min_cost = MAX_INT, last_stop;                                              /* n: counter for nrid, nfl: highest destination, i: highest stop */

  /* nfl computation */
  for (n = 0; n < nrid; n++) {
    if (*(dests + n) > nfl) {                                                  /* For each rider check if his destination is higher than the current highest destination */
      nfl = *(dests + n);                                                                                        /* If yes, then save the new highest destination as nfl */
    }
  }
  /*******************/

  /* min_cost and last_stop computations */
  for (i = 0; i <= nfl; i++) {
    cost = M(i, nst, nrid, dests);                                                             /* For each possible highest stop the M function returns the minimum cost */
    if (cost < min_cost) {                                                                                /* Check if the new cost is less than the current minimum cost */
      min_cost = cost;                                                                                                       /* If yes, then save it as the new min_cost */
      last_stop = i;                                                                                                  /* Also save the current highest stop as last_stop */
    }
  }
  /***************************************/

  /* print about last_stop */
  if (last_stop == 0)
    printf("No elevator stops\n");
  else
    printf("Last stop at floor %d\n", last_stop);
  /*************************/

  return min_cost;
}


int fw(int a, int b, int nrid, int *dests) {                                                                                              /* a, b: two consecutive stops */
  int n, cost = 0;                                                                                  /* cost: cost to move riders with destinations between stops a and b */
  for (n = 0; n < nrid; n++) {
    if ((a <= *(dests + n)) && (*(dests + n) <= b)) {                                                /* For each rider check if his destination is between stops a and b */
      cost += (*(dests + n) - a <= b - *(dests + n)) ? *(dests + n) - a : b - *(dests + n);  /* If yes, then add the cost to move to his destination from stop a or stop b,
                                                                                                                                        depending on which one is closer */
    }
  }
  return cost;
}


int M(int i, int j, int nrid, int *dests) {                                                                                                         /* j: number of stops*/
  int cost, min_cost = MAX_INT, k;                                                                                     /* cost: local cost, min_cost: local minimum cost */
  if (j == 0) {
    min_cost = fw(0, MAX_INT, nrid, dests);                                       /* In case of 0 stops, min_cost is equal to the sum of floors that riders have to walk */
  }
  else {
    for (k = 0; k <= i; k++) {                                                                                      /* For each possible previous stop, compute the cost */
      cost = M(k, j - 1, nrid, dests) - fw(k, MAX_INT, nrid, dests) + fw(k, i, nrid, dests) + fw(i, MAX_INT, nrid, dests);        /* Implementation of the given formula */
      if (cost < min_cost) {                                                                              /* Check if the new cost is less than the current minimum cost */
        min_cost = cost;                                                                                                     /* If yes, then save it as the new min_cost */
      }
    }
  }
  return min_cost;
}


#endif




#ifdef MEM


int fw(int a, int b, int nrid, int *dests);                                                             /* This function computes the cost between two consecutive stops */


int M(int i, int j, int nrid, int *dests, int **pM);                                                              /* This function recursively computes the minimum cost */


int solve(int nrid, int nst, int *dests) {                                                                                                 /* Recursive with memorization*/
  int n, nfl = 0, i, j, cost, min_cost = MAX_INT, last_stop, **pM;                   /* n: counter for nrid, nfl: highest destination, i: highest stop, j: number of stops,
                                                                                                                                                  pM: 2D array for costs */

  /* nfl computation */
  for (n = 0; n < nrid; n++) {
    if (*(dests + n) > nfl) {                                                  /* For each rider check if his destination is higher than the current highest destination */
      nfl = *(dests + n);                                                                                        /* If yes, then save the new highest destination as nfl */
    }
  }
  /*******************/

  /* memory allocation and check about it */
  pM = malloc((nfl + 1) * sizeof(int *));
  if (pM == NULL) {                                                                                     /* In case of unsuccefull memory allocation, finish the function */
    return -1;
  }
  for (i = 0; i <= nfl; i++) {
    *(pM + i) = malloc(nst * sizeof(int));
    if(*(pM + i) == NULL) {                                                                             /* In case of unsuccefull memory allocation, finish the function */
      return -1;
    }
  }
  /****************************************/

  /* pM initialization */
  for (i = 0; i <= nfl; i++) {
    for (j = 0; j <= nst; j++) {
      pM[i][j] = -1;                                                                                                             /* Initialize every element of pM to -1 */
    }
  }
  /************************/

  /* min_cost and last_stop computations */
  for (i = 0; i <= nfl; i++) {
    cost = M(i, nst, nrid, dests, pM);                                                        /* For each possible highest stop, the M function returns the minimum cost */
    if (cost < min_cost) {                                                                                /* Check if the new cost is less than the current minimum cost */
      min_cost = cost;                                                                                                       /* If yes, then save it as the new min_cost */
      last_stop = i;                                                                                                  /* Also save the current highest stop as last_stop */
    }
  }
  /***************************************/

  /* free allocated memory*/
  for (i = 0; i <= nfl; i++) {
    free(*(pM + i));
  }
  free(pM);
  /************************/

  /* print about last_stop */
  if (last_stop == 0)
    printf("No elevator stops\n");
  else
    printf("Last stop at floor %d\n", last_stop);
  /*************************/

  return min_cost;
}


int fw(int a, int b, int nrid, int *dests) {                                                                                              /* a, b: two consecutive stops */
  int n, cost = 0;                                                                                  /* cost: cost to move riders with destinations between stops a and b */
  for (n = 0; n < nrid; n++) {
    if ((a <= *(dests + n)) && (*(dests + n) <= b)) {                                                /* For each rider check if his destination is between stops a and b */
      cost += (*(dests + n) - a <= b - *(dests + n)) ? *(dests + n) - a : b - *(dests + n);  /* If yes, then add the cost to move to his destination from stop a or stop b,
                                                                                                                                        depending on which one is closer */
    }
  }
  return cost;
}


int M(int i, int j, int nrid, int *dests, int **pM) {
  int cost, min_cost = MAX_INT, k;                                                            /* cost: local cost, min_cost: local minimum cost, k: previous stop from i */
  if (pM[i][j] == -1) {                                                                                                /* If the current element has not been calculated */
    if (j == 0) {
      min_cost = fw(0, MAX_INT, nrid, dests);                                     /* In case of 0 stops, min_cost is equal to the sum of floors that riders have to walk */
      pM[i][j] = min_cost;                                                                                                                          /* Save the min_cost */
    }
    else {
      for (k = 0; k <= i; k++) {                                                                                                    /* For each possible k, compute cost */
        cost = M(k, j - 1, nrid, dests, pM) - fw(k, MAX_INT, nrid, dests) + fw(k, i, nrid, dests) + fw(i, MAX_INT, nrid, dests);  /* Implementation of the given formula */
        if (cost < min_cost) {                                                                            /* Check if the new cost is less than the current minimum cost */
          min_cost = cost;                                                                                                   /* If yes, then save it as the new min_cost */
          pM[i][j] = min_cost;                                                                                                                      /* Save the min_cost */
        }
      }
    }
  }
  return pM[i][j];
}


#endif




#ifdef DP


int fw(int a, int b, int nrid, int *dests);                                                             /* This function computes the cost between two consecutive stops */


int M(int i, int j, int nrid, int *dests, int **pM, int **pK);                                                    /* This function dynamically computes the minimum cost */


int solve(int nrid, int nst, int *dests) {                                                                                                        /* Dynamic programming */
  int n, nfl = 0, i, j, cost, min_cost = MAX_INT, last_stop = 0, **pM, **pK, *stop, stops;               /* n: counter for nrid, nfl: highest destination, i: highest stop,
                                                                                   j: number of stops, pM: 2D array for costs, pK: 2D array for k (previous stop from i) */

  /* nfl computation */
  for (n = 0; n < nrid; n++) {
    if (*(dests + n) > nfl) {                                                  /* For each rider check if his destination is higher than the current highest destination */
      nfl = *(dests + n);                                                                                        /* If yes, then save the new highest destination as nfl */
    }
  }
  /*******************/

  /* memory allocation and check about it */
  pM = malloc((nfl + 1) * sizeof(int *));
  if (pM == NULL) {                                                                                     /* In case of unsuccefull memory allocation, finish the function */
    return -1;
  }
  pK = malloc((nfl + 1) * sizeof(int *));
  if (pK == NULL) {                                                                                     /* In case of unsuccefull memory allocation, finish the function */
    return -1;
  }
  stop = malloc(nst * sizeof(int));
  if (stop == NULL) {                                                                                   /* In case of unsuccefull memory allocation, finish the function */
    return -1;
  }
  for (i = 0; i <= nfl; i++) {
    *(pM + i) = malloc((nst + 1) * sizeof(int));
    if(*(pM + i) == NULL) {                                                                             /* In case of unsuccefull memory allocation, finish the function */
      return -1;
    }
    *(pK + i) = malloc((nst + 1) * sizeof(int));
    if(*(pK + i) == NULL) {                                                                             /* In case of unsuccefull memory allocation, finish the function */
      return -1;
    }
  }
  /****************************************/

  /* min_cost and last_stop computations */
  for (j = 0; j <= nst; j++) {
    for (i = 0; i <= nfl; i++) {
      cost = M(i, j, nrid, dests, pM, pK);
      if (cost < min_cost) {
        min_cost = cost;
        last_stop = i;
      }
      printf("%d\t", cost);
    }
    putchar('\n');
    /*
    // print elements of pK
    for (i = 0; i <= nfl; i++) {
      printf("k = %d\t", pK[i][j]);  // Usefull for understanding the sequence of the optimum stops
    }
    putchar('\n');
    putchar('\n');
    */
  }
  /***************************************/

  /* free allocated memory*/
  for (i = 0; i <= nfl; i++) {
    free(*(pM + i));
  }
  free(pM);
  /************************/

  /* save stops*/
  if (nst == 0) {                                                                                  /* If nst != 0 the value of stop[0] comes out from the following loop */
    stop[0] = 0;
  }
  for (j = nst, stop[j] = last_stop; j > 0; j--) {
    stop[j - 1] = pK[stop[j]][j];                                                        /* The k value of each stop indicates the floor of the previous stop (top-down) */
  }
  /*************/

  /* free allocated memory*/
  for (i = 0; i <= nfl; i++) {
    free(*(pK + i));
  }
  free(pK);
  /************************/

  /* counting non-zero stops */
  for (stops = 0, j = nst; stop[j] != 0; j--) {
    stops ++;
  }
  /***************************/

  /* print about stops */
  if (stops == 0) {
    printf("No elevator stops\n");
  }
  else if (stops == 1 ) {
    printf("Elevator stop is:");
    printf(" %d\n", stop[1]);
  }
  else {
    printf("Elevator stops are:");
    for (j = nst - stops + 1; j <= nst; j++) {
      printf(" %d", stop[j]);
    }
    putchar('\n');
  }
  /*********************/

  /* free allocated memory*/
  free(stop);
  /************************/

  return min_cost;
}


int fw(int a, int b, int nrid, int *dests) {                                                                                              /* a, b: two consecutive stops */
  int n, cost = 0;                                                                                  /* cost: cost to move riders with destinations between stops a and b */
  for (n = 0; n < nrid; n++) {
    if ((a <= *(dests + n)) && (*(dests + n) <= b)) {                                                /* For each rider check if his destination is between stops a and b */
      cost += (*(dests + n) - a <= b - *(dests + n)) ? *(dests + n) - a : b - *(dests + n);  /* If yes, then add the cost to move to his destination from stop a or stop b,
                                                                                                                                        depending on which one is closer */
    }
  }
  return cost;
}


int M(int i, int j, int nrid, int *dests, int **pM, int **pK) {
  int cost, min_cost = MAX_INT, k;                                                            /* cost: local cost, min_cost: local minimum cost, k: previous stop from i */
  if (j == 0) {
    min_cost = pM[i][0] = fw(0, MAX_INT, nrid, dests);                            /* In case of 0 stops, min_cost is equal to the sum of floors that riders have to walk */
    pK[i][0] = 0;                                                                                             /* Obviously in this case, the only valid value for k is 0 */
  }
  else {
    for (k = 0; k <= i; k++) {                                                                                                      /* For each possible k, compute cost */
      cost = pM[k][j - 1] - fw(k, MAX_INT, nrid, dests) + fw(k, i, nrid, dests) + fw(i, MAX_INT, nrid, dests);                    /* Implementation of the given formula */
      if (cost < min_cost) {
        min_cost = cost;                                                                                                     /* If yes, then save it as the new min_cost */
        pM[i][j] = min_cost;                                                                                                                        /* Save the min_cost */
        pK[i][j] = k;                                                                                                                                      /* Save the k */
      }
    }
  }
  return min_cost;
}


#endif




#ifdef BF


int fw(int a, int b, int nrid, int *dests);                                                             /* This function computes the cost between two consecutive stops */


int solve(int nrid, int nst, int *dests) {                                                                                                                /* Brute force */
  int n, nfl = 0, j, *stop, *best_stop, cost, min_cost = MAX_INT, end = FALSE;

  /* nfl computation */
  for (n = 0; n < nrid; n++) {
    if (*(dests + n) > nfl) {                                                  /* For each rider check if his destination is higher than the current highest destination */
      nfl = *(dests + n);                                                                                        /* If yes, then save the new highest destination as nfl */
    }
  }
  /*******************/

  /* memory allocation and check about it */
  stop = malloc((nst + 2) * sizeof(int));
  best_stop = malloc((nst + 1) * sizeof(int));
  /****************************************/

  /* intialization of stop array */
  stop[0] = 0;
  for (j = 1; j < nst + 2; j++) {
    stop[j] = MAX_INT;                                            /* Initialize every element as MAX_INT so fw function will be able to compute the cost after last stop */
  }
  /*******************************/

  /* case of elevator immobility */
  if (nst == 0 || nfl == 0) {
    min_cost = fw(stop[0], stop[1], nrid, dests);                                   /* Everyone has to go to his destination by the stairs or all the destinations are 0 */
    best_stop[0] = 0;                                                                                 /* In this case there are not higher stops than 0, so it is enough */
    end = TRUE;                                                                                                                               /* Skip the following loop */
  }
  /*******************************/

  while (!end) {
    /* initialize and compute cost */
    cost = 0;                                                                                                           /* For each new stops combination reset the cost */
    for (j = 0; stop[j] != MAX_INT; j++) {
      cost += fw(stop[j], stop[j+1], nrid, dests);                                                              /* Accumulate the cost for the current stops combination */
    }
    /*******************************/

    /* best stops combination currently */
    if (cost < min_cost) {
      min_cost = cost;                                                                                                                                  /* Save its cost */
      for (j = 0; j < nst+1; j++) {
        best_stop[j] = stop[j+1];                                                                                                                      /* Save its stops */
      }
    }
    /******************************/

    /* check for end condition */
    for (j = nst; j > 0; j--) {
      if (stop[j] != nfl - (nst - j) ) {                                                  /* If every stop[j] has not the biggest possible value, keep runnning the loop */
        break;
      }
      if (stop[1] == nfl - (nst - 1) ) {
        end = TRUE;                                                                         /* If every stop[j] has the biggest possible value, enable the end condition */
      }
    }
    /****************************/

    /* combinations generator */
    if (!end) {
      for (j = 1; j <= nst; j++) {
        if (stop[j] == MAX_INT) {
          stop[j] = j;                                                          /* In case of first usage, initialize the new higher stop at the smallest possible floor */
          break;                                                                                                                         /* Go check the new combination */
        }
        else if ( ( stop[j] < nfl ) && ( stop[j] < stop[j+1] - 1 ) ) {
          stop[j]++;                                                                                                 /* If the stop is within limits, increase the floor */
          break;                                                                                                                         /* Go check the new combination */
        }
        else stop[j] = j;                        /* If the current stop is over the limits, reset it at its lowest possible floor, and continue to update the upper stop */
      }
    }
    /*************************/
  }

  /* print about stops */
  if (best_stop[0] == 0) {
    printf("No elevator stops\n");
  }
  else if (best_stop[1] == MAX_INT) {
    printf("Elevator stop is:");
    printf(" %d\n", best_stop[0]);
  }
  else {
    printf("Elevator stops are:");
    for (j = 0; best_stop[j] != MAX_INT && j < nst; j++) {
      printf(" %d", best_stop[j]);
    }
    putchar('\n');
  }
  /*********************/

  return min_cost;
}


int fw(int a, int b, int nrid, int *dests) {                                                                                              /* a, b: two consecutive stops */
  int n, cost = 0;                                                                                  /* cost: cost to move riders with destinations between stops a and b */
  for (n = 0; n < nrid; n++) {
    if ((a <= *(dests + n)) && (*(dests + n) <= b)) {                                                /* For each rider check if his destination is between stops a and b */
      cost += (*(dests + n) - a <= b - *(dests + n)) ? *(dests + n) - a : b - *(dests + n);  /* If yes, then add the cost to move to his destination from stop a or stop b,
                                                                                                                                        depending on which one is closer */
    }
  }
  return cost;
}


#endif

