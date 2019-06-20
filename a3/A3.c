#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#define TOTAL 4000

void *getMoney();

struct Fund{
  int moneyTaken;
  int moneyAvail;
};

struct Student{
  pthread_t tid;
  char name;
  double delay;
};

struct Fund schFnd = {0, 4000};
pthread_mutex_t mutex;

int main(){
  struct Student s0 = { 0, 'A', .1};
  struct Student s1 = { 0, 'B', .3};
  struct Student s2 = { 0, 'C', .5};

  pthread_setconcurrency(3);

  pthread_create(&s0.tid, NULL, (void *(*)(void *))getMoney, &s0);
  pthread_create(&s1.tid, NULL, (void *(*)(void *))getMoney, &s1);
  pthread_create(&s2.tid, NULL, (void *(*)(void *))getMoney, &s2);

  pthread_join(s0.tid, NULL);
  pthread_join(s1.tid, NULL);
  pthread_join(s2.tid, NULL);

  printf("Total Money given: %d\n", schFnd.moneyTaken);
  return 0;
}

void *getMoney(struct Student *s){
  int moneyTaken = 0;
  while (schFnd.moneyAvail > 1){
    pthread_mutex_lock(&mutex);
    int remItems = (int)ceil(schFnd.moneyAvail * 0.25);
    sleep(s->delay);
    schFnd.moneyAvail -= remItems;
    pthread_mutex_unlock(&mutex);

    printf("thread %c takes %d money.\n", s->name, remItems);
    moneyTaken += remItems;
  }
  schFnd.moneyTaken += moneyTaken;
}

