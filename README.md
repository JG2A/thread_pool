# Threadpool
When thread pools are used, a task is submitted to the pool and executed by a thread from the pool. Work is submitted to the pool using a queue, and an available thread removes work from the queue. If there are no available threads, the work remains queued until one becomes available. If there is no work, threads await notification until a task becomes available. This project involves creating and managing a thread pool, and it may be completed using Pthreads and POSIX synchronization.

## Identifying Information

* Name: Jose Garcia & Evan Figueroa
* Email: jgarcia2@chapman.edu 
* Course: CPSC 380
* Assignment: 4

## Source Files

* client.c
* threadpool.h
* threadpool.c

## References

* 

## Known Errors

*

## Build Insructions

* <code>g++ *.c -o client</code>

## Execution Instructions

* In order to run type  <code>./client</code>

