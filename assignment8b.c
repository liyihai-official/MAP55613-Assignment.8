/**
 * @file assignment8b.c
 * @brief This is the multi-thread version of assignment8
 * @author LI Yihai
 * @date 2024-01-07
 * @version 8.0.3
*/
#include "function.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* Declare the mutex and the condition variable. */
pthread_mutex_t mutex;
pthread_cond_t cond;

/* Initialize the id of current thread. */
int current_thread = 0;

/* Initialized the shared data */
const char FILE_NAME[] = "assignment8b_result.txt";

coord ** coords;
const int N_x = 50;
const int N_t = N_x*N_x*2*(T_MAX - T_MIN)+1;

const double x_delta = (X_MAX - X_MIN) / N_x;
const double t_delta  = x_delta * x_delta * 0.5;

/* Thread function which will be operated in each thread. */
void *thread_function(void *arg);


int main(void) {
    /* Initialize the informations of threads */
    int N_p = 5; 
    thread_msg msgs[5];
    pthread_t threads[5];

    coord_2d_array_alloc(&coords, 2, N_x+1); /* Initialize 2d array (2,N_x+1) pool for iteration*/

    initial_condition(coords[0], N_x, x_delta); /* Load initial condition */
    
    /* (Create if no file) Write keys (x,t,u,err) to file (mode w) and close it.*/
    write_keys_to_file(FILE_NAME, 'w');
    FILE * fp = fopen(FILE_NAME, "a");
    if (fp == NULL) { 
        return_message(2);
    }
    
    /* Initialize the pointer of message of each thread. */
    for (int i = 0; i<N_p; i++){
        msgs[i].fp = fp;
        msgs[i].N_p = N_p;
        msgs[i].p_id = i;
    }

    /* Initialize the mutex lock and condition */
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    /* Create pthreads */
    for (int i = 0; i < N_p; ++i) {
        pthread_create(&threads[i], NULL, thread_function, &msgs[i]);
    }

    /* Wait pthreads complete */
    for (int i = 0; i < N_p; ++i) {
        pthread_join(threads[i], NULL);
    }

    /* Destory the mutex lock and condition */
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    
    /* Close file */
    if (fclose(fp) != 0) {
        return_message(3);
    }
    coord_2d_array_free(&coords, 2); /* Free allocated memory */

    return 0;
}








/**
 * @brief Function executed by each thread in the heat simulation.
 *
 * This function controls the behavior of each thread in a multi-threaded simulation. 
 * It involves synchronization using mutexes and condition variables to ensure 
 * that each thread processes its designated part of the computation in the correct order.
 *
 * @param arg Pointer to a thread_msg structure containing thread-specific information.
 *
 * @return Always returns NULL. 
 *
 * The function casts the void pointer 'arg' to a 'thread_msg' pointer.
 * Each thread uses its thread ID to wait for its turn to process its part of the simulation.
 * The 'epoch' function is called to perform the main computation.
 * If the thread is the last one in the sequence, it writes the results to a file.
 * Mutex locks and condition variables are used to synchronize thread execution.
 */
void *thread_function(void *arg) {
    thread_msg * msg = (thread_msg *) arg;
    int thread_id = msg->p_id;

    for (int t = 1; t < N_t; t++) {  /* Each thread runs X times */
        
        pthread_mutex_lock(&mutex); /* Lock the mutex */

        /* Wait until it's the current thread's turn */
        while (thread_id != current_thread) {
            pthread_cond_wait(&cond, &mutex);
        }        
        int cur = t%2;
        int pre = (t+1)%2;

        /* A unified function for compute values for next step. */
        epoch(t, cur, pre, N_x, &coords, x_delta, t_delta);

        if (thread_id+1 == msg->N_p){ /* Print the results if it is the last thread */
            for (int x=0; x <= N_x; x++){
                fprintf(msg->fp, "%lf %lf %.8lf %.8lf\n", coords[pre][x].x, coords[pre][x].t, coords[pre][x].u, coords[pre][x].err);
            }
        }
        
        /* Update the ID of the next thread to execute */
        current_thread = (current_thread + 1) % msg->N_p;

        /* Notify other threads */
        pthread_cond_broadcast(&cond);

        /* Unlock the mutex */
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}