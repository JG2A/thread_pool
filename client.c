#include "threadpool.h"
#include <stdio.h>
#include <unistd.h>

struct data {
  int a;
  int b;
};
void add(void *param){
  struct data *temp;
  temp = (struct data *)param;
  printf("I add two values %d and %d, result = %d\n", temp->a, temp->b, temp->a + temp->b);
}

int main (){
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
  sleep(3); // wait for threads to finish
  pool_shutdown();
  
  return 0;

}