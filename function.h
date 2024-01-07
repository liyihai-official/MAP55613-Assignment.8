/**
 * @file function.h
 * @brief This is the function prototypes for assignment 8
 * @author LI Yihai
 * @date 2024-01-07
 * @version 8.0.3
*/
#ifndef function_h
#define function_h

#include "structure.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#endif /* function_h */


int return_message(const int err);
int write_keys_to_file(char const * const file_name, const char MODE);

int coord_2d_array_alloc(coord ***in, const int R, const int C);
void coord_2d_array_free(coord ***in, const int R);

void initial_condition(coord *in, const int N, const double dx);
double boundary_condition(const double x, const double t);
double iteration_function(const double u1, const double u2);
double true_function(const double x, const double t);
void epoch(int t, int cur, int pre, int N_x, coord *** coords, double x_delta, double t_delta);