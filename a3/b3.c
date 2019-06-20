#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

void *getMoney();

struct Fund{
  int moneyTaken;
  int moneyAvail;
};

struct Student{
  pthread_t thread;
  char name;
  int moneyTaken;
  double delay;
};

struct Fund schFnd = {0, 4000};
  
pthread_mutex_t mutex;

int main(){
  struct Student s0 = { 0, 'A', 0, .1};
  struct Student s1 = { 0, 'B', 0, .3};
  struct Student s2 = { 0, 'C', 0, .5};

  
  pthread_setconcurrency(3);

  pthread_create(&s0.thread, NULL, (void *(*)(void *))getMoney, &s0);
  pthread_create(&s1.thread, NULL, (void *(*)(void *))getMoney, &s1);
  pthread_create(&s2.thread, NULL, (void *(*)(void *))getMoney, &s2);

  pthread_join(s0.thread, NULL);
  pthread_join(s1.thread, NULL);
  pthread_join(s2.thread, NULL);

  printf("Total money given: %d\n", schFnd.moneyTaken);

  return 0;
}

void *getMoney(struct Student *s){
  while (schFnd.moneyAvail > 1){
    pthread_mutex_lock(&mutex);
    int money = (int)ceil(schFnd.moneyAvail * 0.25);
    sleep(s->delay);
    schFnd.moneyAvail -= money;
    pthread_mutex_unlock(&mutex);

    printf("thread %c takes %d money\n", s->name, money);
    s->moneyTaken += money;
  }
  schFnd.moneyTaken += s->moneyTaken;
}

