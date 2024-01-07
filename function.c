/**
 * @file function.c
 * @brief This is the function library for assignment 8
 * @author LI Yihai
 * @date 2024-01-07
 * @version 8.0.3
*/

#include "function.h"

/** 
 * @brief Returns an error message based on the error code.
 * @param err Error code.
 * @return Error code passed to the function.
 */
int return_message(const int err){
    if (err == 1){
        printf("Allocation Error\n");
        return 1;
    } else if (err == 2) {
        printf("File Open Error\n");
        return 2;
    } else if (err == 3){
        printf("File Close Error\n");
        return 3;
    }
    
    return 0;
}

/** 
 * @brief Writes keys to a file.
 * @param file_name Name of the file to write to.
 * @param MODE Mode in which the file is opened.
 * @return 0 on success, error code on failure.
 */
int write_keys_to_file(char const * const file_name, const char MODE){
    FILE * fp = fopen(file_name, &MODE);
    if (fp == NULL){
        return return_message(2);
    }
    
    fprintf(fp, "x t u err\n");
    if (fclose(fp) != 0) {
        return return_message(3);
    };
    
    return 0;
}

/** 
 * @brief Allocates memory for a 2D array of coordinates.
 * @param in Pointer to the 2D array.
 * @param R Number of rows.
 * @param C Number of columns.
 * @return 0 on success, error code on failure.
 */
int coord_2d_array_alloc(coord ***in, const int R, const int C){
    *in = aligned_alloc(8, R * sizeof(coord*));
    if (*in == NULL) {
        return return_message(1);
    }
    for (int r = 0; r<R; r++){
        (*in)[r] = aligned_alloc(32, C * sizeof(coord));
        if ((*in)[r] == NULL) {
            return return_message(1);
        }
    }
    return 0;
}

/** 
 * @brief Frees memory allocated for a 2D array of coordinates.
 * @param in Pointer to the 2D array.
 * @param R Number of rows.
 */
void coord_2d_array_free(coord ***in, const int R){
    for (int r = 0; r < R; r++) {
        free((*in)[r]);
    }
    free(*in);
}



/** 
 * @brief Sets the initial condition for a set of coordinates.
 * @param in Array of coordinates.
 * @param N Number of coordinates.
 * @param dx Delta x.
 */
void initial_condition(coord *in, const int N, const double dx){
    for (int x=0; x <= N; x++){
        in[x].x = x*dx;
        in[x].t = 0;
        in[x].u = sin(PI*in[x].x);
    }
}

/** 
 * @brief Defines the boundary condition.
 * @param x Spatial coordinate.
 * @param t Temporal coordinate.
 * @return Result of the boundary condition function.
 */
double boundary_condition(const double x, const double t){
    return x*t*0;
}

/** 
 * @brief Defines the iteration function for the simulation.
 * @param u1 Value at the first point.
 * @param u2 Value at the second point.
 * @return Result of the iteration function.
 */
double iteration_function(const double u1, const double u2){
    return u1*0.5 + u2*0.5;
}

/** 
 * @brief Represents the true function for comparison.
 * @param x Spatial coordinate.
 * @param t Temporal coordinate.
 * @return Result of the true function.
 */
double true_function(const double x, const double t){
    return exp(-PI*PI*t)*sin(PI*x);
}

/** 
 * @brief Performs a single epoch of the simulation.
 * @param t Current time step.
 * @param cur Index of the current coordinate set.
 * @param pre Index of the previous coordinate set.
 * @param N_x Number of spatial steps.
 * @param coords Pointer to the 2D array of coordinates.
 * @param x_delta Delta x.
 * @param t_delta Delta t.
 */
void epoch(int t, int cur, int pre, int N_x, coord *** coords, double x_delta, double t_delta){
    for (int x = 0; x <= N_x; x++){
        (*coords)[cur][x].x = x*x_delta;
        (*coords)[cur][x].t = t*t_delta;
        if (x==0 || x==N_x) {
            (*coords)[pre][x].u = boundary_condition((*coords)[cur][x].x, (*coords)[cur][x].t);
        } else {
            (*coords)[cur][x].u = iteration_function((*coords)[pre][x-1].u, (*coords)[pre][x+1].u);
        }
        (*coords)[cur][x].err = (*coords)[cur][x].u - true_function((*coords)[cur][x].x, (*coords)[cur][x].t);
    }
}

