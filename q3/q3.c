#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

if(argc < 2){
   printf("too few cmds\n");
   exit(1);
}

for(int i = 0; i <= argc; i++){
   argv[i -1] = argv[i];
}

char *cmdEnt = argv[0];
char **argsEnt = argv;
pid_t pid;
pid = fork();

if(pid == 0){
   printf("\nchild:\n");
   execvp(cmdEnt, argsEnt);
   exit(0);
}
else if(pid > 0){
   printf("\nParent waiting on child\n");
   wait(NULL);
   exit(0);
}
else{
   printf("error\n");
   exit(1);
}
exit(0);
}
