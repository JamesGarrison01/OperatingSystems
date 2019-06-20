#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

pid_t pid;
int p[2];

if(argc < 3){
  // printf("Invalid amount of arguments\n");
  // exit(1);
}

for(int i = 0; i <= argc; i++){
   argv[i -1] = argv[i];
}
pipe(p);
pid = fork();

if(pid == 0){
   puts("Starting Child");
   puts("Please Enter city then population. Hit ctrl D to finish");
   close(p[0]);
   dup2(p[1], 1);
   close(p[1]);
   execvp(argv[0], argv);
}
else if(pid > 0){
   wait(NULL);
   printf("Starting Parent");
   close(p[1]);
   dup2(p[0], 0);
   close(p[0]);
   execvp(argv[1], argv);
}
else{
   printf("\nError bad PID\n");
   exit(1);
}

}
