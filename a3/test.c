#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Student{
   pthread_t tid;
   char name;
   int money;
};

struct fund{
   int money;
};

void getMoney(struct Student S, struct fund f);

int main(){
   struct Student s0 = {0, 'A', 0};
   struct Student s1 = {0, 'B', 0};
   struct Student s2 = {0, 'C', 0};
   
   struct fund fnd = {4000};

   pid_t pid;
   pid_t pid1;
   pid = fork();

   if(pid == 0){
      pid1 = fork();
      if(pid1 == 0){
         printf("\ngrand:\n");
         getMoney(s0, fnd);
         exit(0);
         printf("should not run");
      }
      else if(pid1 > 0){
         printf("\nchild:\n");
         getMoney(s1, fnd);
         exit(0);
         printf("should not run");
      }
      else{
         printf("should not run");
      }
      exit(0);
      printf("should not run");
   }
   else if(pid > 0){
      printf("\nparent:\n");
      getMoney(s2, fnd);
      exit(0);
      printf("should not run");
   }
   else{
      printf("should not run");
   }
}

void getMoney(struct Student s, struct fund f){
   if(f.money > 0){
      int money = f.money * .25;
      f.money = f.money - money;
      s.money = s.money + s.money;
   }
}

