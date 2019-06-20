#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdbool.h>

static int MAX = 20;

void redirect(char *argv, char *inFile, char *dirPoint);
bool multiple(char **argv, char **arg2, int *count);


int main(){

   int fd[2], fd2[2];
   bool reDirIn, reDirOut, gFlag = false, lFlag = false, mFlag = false;
   char *line = NULL;
   char *path, *argv[MAX], *arg2[MAX], *arg3[MAX], buf[80], fIn[80], fOut[80], n, *p;
   int m, status, inword, continu;
   int count = 0;

   for(int i = 0; i < MAX; i++){
      argv[i] = NULL;
      arg2[i] = NULL;
      arg3[i] = NULL;
   }


   while(1) {
   pid_t pid;
   size_t size;
   reDirIn = false;
   reDirOut = false;

   inword = 0;
   p = buf;
   m = 0;
   continu=0;

   
   printf("\nshhh> ");

   while((n = getchar()) != '\n'  || continu){

	   if ( n ==  ' ' ) { 
	      if ( inword ) {
            inword = 0;
            *p++ = 0;
         } 
	   }
	   else if ( n == '\n' ) continu = 0;
   	else if ( n == '\\' && !inword ) continu = 1;
      else {
          if ( !inword ) {
   		 inword = 1;
   		 argv[m++] = p;
      	 *p++ = n;
   	   }
	     else 
	        *p++ = n;
	   }
   }

   if(m > 1){
      for(int i = 1; i < m; i++){
         if(strcmp(argv[i], "|") == 0){
          // mFlag = multiple(argv, arg2, &count);
            *arg2 = strtok(*argv, "|");
            mFlag = true;
            break;
         }
      }
    for(int i = 1; i < m; i++){
       if(strcmp(argv[i], "<") == 0){
            *arg2 = strtok(*argv, ">");
            gFlag = true;
       
       }
     }
    for(int i = 1; i < m; i++){
      if(strcmp(argv[i], ">") == 0){
            *arg2 = strtok(*argv, "<");
            lFlag = true;
      }
   }
  }
   if(mFlag){
      *p++ = 0;
      argv[m] = 0;
    while(arg2[count] != NULL && count < MAX){
       count++;
   }
   while(count){
      count--;
      pid = fork();
      *arg3 = arg2[count];
      printf("arg2 count: %s\n", *arg3);
      if(pid == 0){
         execvp(arg3[0], arg3);
      }
      wait(&status);
   }
   for(int i = 1; i < m; i++){
      if(strcmp(argv[i], "<") == 0){
            *arg2 = strtok(*argv, "|>");
         }
    }

    for(int i = 1; i < m; i++){
         if(strcmp(argv[i], ">") == 0){
            *arg3 = strtok(*argv, "|<");
         }
    }
   }
   if(lFlag){
    //  redirect(argv[0], fIn, "<");
   }
   if(gFlag){

   }
   else if(!mFlag && !lFlag && !gFlag){
      *p++ = 0;
      argv[m] = 0;

      if ( strcmp(argv[0],"exit") == 0 ) exit (0);

      if ( fork() == 0 ){
   	   execvp( argv[0], argv );
      	printf ( "%s didn't exec \n ", argv[0]);
	   }

      wait(&status);
      }
   }
return 0;
}

void redirect(char *argv, char *inFile, char *dirPoint){
   char *split = strtok(argv, dirPoint);
   if(split != NULL){
      strcpy(argv, split);
   }
   else
      return;
   

}
bool multiple(char **argv, char **arg2, int *count){
 //  *arg2 = strtok(*argv, "|");
 //  int count2 = sizeof(arg2);

 //  for( int i = 0; i <= count2; i++){

  // }
   return true;
}
