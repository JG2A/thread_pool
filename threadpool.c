#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define QUEUE_SIZE 10
#define MAX_THREADS 3

#define TRUE 1

typedef struct {
    void (*function)(void *p);
    void *arg;
} task_t;

task_t worktodo[QUEUE_SIZE]; // task queue
int head = 0; // head of the queue
int tail = 0; // tail of the queue
int worktodo_count = 0; // number of tasks in the queue

pthread_t threads[MAX_THREADS];
pthread_mutex_t queue_lock; // mutex for queue access
sem_t task_sem; // semaphore to track tasks in the queue


int enqueue(task_t t) {
    pthread_mutex_lock(&queue_lock);

    if (worktodo_count == QUEUE_SIZE) {
        // Queue is full
        pthread_mutex_unlock(&queue_lock);
        return 1;
    }

    worktodo[tail] = t;
    tail = (tail + 1) % QUEUE_SIZE;
    worktodo_count++;

    pthread_mutex_unlock(&queue_lock);
    sem_post(&task_sem); // Signal that a task is available
    return 0;
}

int dequeue(task_t *t) {
    pthread_mutex_lock(&queue_lock);

    if (worktodo_count == 0) {
        // Queue is empty
        pthread_mutex_unlock(&queue_lock);
        return 1;
    }

    *t = worktodo[head];
    head = (head + 1) % QUEUE_SIZE;
    worktodo_count--;

    pthread_mutex_unlock(&queue_lock);
    return 0;
}

void execute(void (*function)(void *p), void *p) {
    function(p);
}

void pool_submit(void (*somefunction)(void *p), void *p) {
    task_t new_task;
    new_task.function = somefunction;
    new_task.arg = p;

    if (enqueue(new_task) != 0) {
        fprintf(stderr, "Failed to submit task: Queue is full\n");
    }

}

void pool_init(void) {
    pthread_mutex_init(&queue_lock, NULL);
    sem_init(&task_sem, 0, 0);

    for (int i = 0; i < MAX_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, worker, NULL) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
}

void pool_shutdown(void) {
    for (int i = 0; i < MAX_THREADS; i++) {
        // Submit NULL tasks to signal threads to exit
        pool_submit(NULL, NULL);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&queue_lock);
    sem_destroy(&task_sem);
}

void *worker() {
    while (TRUE) {
        sem_wait(&task_sem); // Wait for a task to be available

        task_t task;
        if (dequeue(&task) == 0) {
            if (task.function == NULL) {
                // NULL task signals the thread to exit
                break;
            }
            execute(task.function, task.arg);
        }
    }
    return NULL;
}