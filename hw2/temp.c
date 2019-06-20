#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


int main(int argc, char *argv[]){
   char *path, arg[20], buf[80], n, *p;
   int m, status, inword, continu;


   while(1){

      inword = 0;
      p = buf;
      m = 0;
      continu = 0;

      printf( "\nshhh> ");

      while ((n = getchar()) != '\n' || continu){
         if(n == ' '){
            if(inword){
               inword = 0;
               *p++ = 0;
            }
         }
         else if(n ==  '\n') continu = 0;
         else if(n == '\\' && !inword) continu = 1;
         else{
            if(!inword){
               inword = 1;
               arg[m++] = p;
               *p++ = n;
            }
            else
               *p++ = n;
         }

      }
      *p++ = 0;
      arg[m] = 0;

      if( strcmp(arg[0], "exit") == 0) exit(0);

      if(fork() == 0){
         execvp(arg[0], arg);
         printf("didn't exec \n");
      }
      wait(&status);
   }
   return 0;
}
