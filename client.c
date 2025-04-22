#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// #include <libc.h>

struct data {
  int a;
  int b;
};
void add(void *param){
  struct data *temp;
  temp = (struct data *)param;
  printf("I add two values %d and %d, result = %d\n", temp->a, temp->b, temp->a + temp->b);
}

int main (int argc, char *argv[]) {
  
  // printf("argv[0]: %s\n", argv[0]);
  // printf("argv[1]: %s\n", argv[1]);
  if (argc > 1 && strcmp(argv[1], "default") == 0) {

    struct data work;
    struct data work2;
    struct data work3;
    struct data work4;
    struct data work5;

    work.a = 5;
    work.b = 10;
    work2.a = 15;
    work2.b = 20;
    work3.a = 25;
    work3.b = 30;
    work4.a = 35;
    work4.b = 40;
    work5.a = 45;
    work5.b = 50;

    // Initialize the thread pool
    pool_init();
    pool_submit(add, &work); // test multiple threads
    pool_submit(add, &work2); // test multiple threads
    pool_submit(add, &work3); // test multiple threads
    pool_submit(add, &work4); // test multiple threads
    pool_submit(add, &work5); // test multiple threads
    // sleep(3); // wait for threads to finish
    pool_shutdown();
    printf("All tasks successfully completed.\n");
  }

  else {
    if (argc < 2) {
      printf("Please provide at least one argument.\n");
      return -1;
    }
    if ((argc-1) % 2 != 0) {
      printf("Please provide an even number of arguments.\n");
      return -1;
    }
    struct data client_work;
    for (int i = 1; i < argc; i++){
      if (i % 2 != 0) {
        client_work.a = atoi(argv[i]);
      }
      else {
        client_work.b = atoi(argv[i]);
        pool_init();
        pool_submit(add, &client_work);
        pool_shutdown();
      }
    }
  }

    
  return 0;

}