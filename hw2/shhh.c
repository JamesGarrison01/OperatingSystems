
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

static int MAX = 20;


bool redirect(char *argv, char *args, char *sign);
void tokenize(char *line, char **args, int *procCount);
char *trim(char *str);
void trim2(char *str);

int main(){
  int status;
  char *line = NULL;
  char buf[80], fIn[80], fOut[80];

  char **argv = (char **)malloc(MAX * sizeof(char *));
  for (int i = 0; i < MAX; i++){
    argv[i] = NULL;
  }

  size_t size;
  pid_t pid;

  while(1){
     bool inFlag = false;
     bool outFlag = false;
     int count = 0;
     int count2 = 0;
     int fd[2];

     printf("\nshhh>");
      
    if(getline(&line, &size, stdin) == EOF){
      break;
    }
    if(strncmp(line, "exit", 4) == 0){
          break;
    }

    strcpy(buf, line);
    int size;
    char *cmd = strtok(line, "|");

    while (cmd != NULL && count < MAX){
      trim(cmd);
      size = strlen(cmd);
      argv[count] = (char *)malloc(size + 1 * sizeof(char));
      strncpy(argv[count++], cmd, size);
      cmd = strtok(NULL, "|");
      
   }

   argv[count] = NULL;
   inFlag = redirect(argv[0], fIn, "<");
   outFlag = redirect(argv[count - 1], fOut, ">");

   for(int i = 0; i<count; i++){
      if(inFlag || outFlag || count > 0){
         pipe(fd);
         pid = fork();
      
         if(pid > 0){
            wait(&status);
         }
         else if(pid == 0){
            if(inFlag && !outFlag && i == 0){
               close(1);
               int fd2 = open(fIn, O_RDONLY);
               dup2(fd2, 0);
               close(fd2);
            }
            if(outFlag && !inFlag && i == (count - 1)){
               close(0);
               int fd2 = open(fOut, O_WRONLY | O_TRUNC | O_CREAT, 0755);
               dup2(fd2, 1);
               close(fd2);
            }
            int j = 0;
            int length = strlen(argv[i]);
            char *argTemp = (char *)malloc(length + 1 * sizeof(char));
            strncpy(argTemp, argv[i], length);
            char *argT[20] = {};
            char *argT2 = strtok(argTemp, " ");
            do{
               int length2 = strlen(argT2);
               argT[j] = (char *)malloc((length2 + 1) * sizeof(char));
               strncpy(argT[j++], argT2, length2);
            }while((argT2 = strtok(NULL, " ")) && j < 20);
            free(argTemp);
            argT[j] = NULL;

      execvp(argT[0], (char *const *)argT);
         }
      }
    }
  }
  for (int i = 0; i < MAX; i++){
    if(argv[i]){
       free(argv[i]);
    }
  }
}


bool redirect(char *argv, char *args, char *sign){
  bool flag = false;
  char *found = strtok(argv, sign);
  if (found != NULL){
    trim(found);
    strcpy(argv, found);
  }
  else
    return flag;

  found = strtok(NULL, " ");
  if (found != NULL){
    trim(found);
    strcpy(args, found);
    flag = true;
  }
  return flag;
}

char *trim(char *str){
  char *end;

  while(isspace((unsigned char)*str)){
     str++;
  }

  if(*str == 0){
    return str;
  }

  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)){
     end--;
  }

  end[1] = '\0';

  return str;
}

