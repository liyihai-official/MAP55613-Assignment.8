/**
 * @file assignment8a.c
 * @brief This is the single thread version of assignment8
 * @author LI Yihai
 * @date 2024-01-07
 * @version 8.0.3
*/
#include "function.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @mainpage Assignment 8
 * 
 * Assignment 8 of MAP55631 C Programming
 * 
 * Description: In this assignment, the two programs are solving the one dimension 
 * heat equation from [0, 1] in 0 to 0.2 seconds which is 
 * @f\[ \frac{\partial}{\partial t}u(t,x) =  \frac{\partial^2}{\partial u^2}u(t,x) @f\]
 * The initial condition is 
 * @f\[ u(0,x) = sin(\pi x) @f\]
 * and the boundary conditions are 
 * @f\[ u(t,0) = u(t,1) = 0 @f\]
 * 
 * Solved it by iterating as 
 * @f\[ u(x, t + \Delta t) =  \left[ u(x+ \Delta x, t) + u(x-\Delta x, t) \right]\frac{1}{2}@f\]
 * ## Features
 * 
 * - Assignment8a is the single thread version
 * - Assignment8b is the single thread version
 */

int main(void){
    /* Initialize essential variables */
    const int N_x = 10;
    const int N_t = N_x*N_x*2*(T_MAX - T_MIN) + 1;

    const double x_delta = (X_MAX - X_MIN) / N_x;
    const double t_delta  = x_delta * x_delta * 0.5;

    const char FILE_NAME[] = "assignment8a_result.txt";

    coord ** coords;

    /* Initialize 2D array as pool for store iteration results. */
    coord_2d_array_alloc(&coords, 2, N_x+1);

    /* Initial condition */
    initial_condition(coords[0], N_x, x_delta);
    
    /* Write Index to file */
    write_keys_to_file(FILE_NAME, 'w');

    FILE * fp = fopen("assignment8a_result.txt", "a"); /* Open file (append mode) */

    /* Start Iteration on status t in 0 < t < N_t*t_delta */
    int cur, pre;

    for (int t = 1; t <= N_t; t++){
        pre = (t+1)%2;
        cur = t%2;

        /* Calling united iteration function */
        epoch(t, cur, pre, N_x, &coords, x_delta, t_delta);

        /* Write previous (t-1) status to file (append mode) */
        for (int x=0; x <= N_x; x++){
            fprintf(fp, "%lf %lf %.8lf %.8lf\n", coords[pre][x].x, coords[pre][x].t, coords[pre][x].u, coords[pre][x].err);
        }
    }
    fclose(fp); 
    return 0;
}