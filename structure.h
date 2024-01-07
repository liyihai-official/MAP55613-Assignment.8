/**
 * @file structure.h
 * @author LI Yihai
 * @version 8.2.3
 * @date 2024-01-07
 * 
 * @brief This is the structure file. Define the structures and the global variables for 
 * solving the question.
*/

#ifndef structure_h
#define structure_h
#endif /* structure_h */

#include <stdio.h>

/** @def PI
 *  @brief The mathematical constant PI.
 */
#define PI 3.1415926535

/** @def T_MIN
 *  @brief Minimum value for time variable 't'.
 */
#define T_MIN 0.0

/** @def T_MAX
 *  @brief Maximum value for time variable 't'.
 */
#define T_MAX 0.2

/** @def X_MIN
 *  @brief Minimum value for spatial variable 'x'.
 */
#define X_MIN 0.0

/** @def X_MAX
 *  @brief Maximum value for spatial variable 'x'.
 */
#define X_MAX 1.0

/** 
 * @struct thread_msg
 * @brief Structure for passing data to threads.
 * @var thread_msg::N_p
 * The number of points.
 * @var thread_msg::p_id
 * The identifier for the thread.
 * @var thread_msg::fp
 * File pointer for thread-specific output.
 */
typedef struct _thread_msg {
    int N_p;
    int p_id;
    FILE * fp;
} thread_msg;

/** 
 * @struct coord
 * @brief Represents a coordinate in the simulation.
 * @var coord::x
 * Spatial coordinate.
 * @var coord::t
 * Temporal coordinate.
 * @var coord::u
 * Solution value at this coordinate.
 * @var coord::err
 * Error estimate at this coordinate.
 */
typedef struct _corrd {
    double x;
    double t;
    double u;
    double err;
} coord;