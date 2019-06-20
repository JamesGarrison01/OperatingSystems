
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

bool findRedirect(char *arg, char *reFile, char *delim);
void tokenize(char *line, char **args, int *procCount);
void trim(char *str);

int main()
{
  int i, status;
  bool redir_out, redir_in;
  char *line = NULL;
  char buf[80], fIn[80], fOut[80];

  char **argv = (char **)malloc(MAX * sizeof(char *));
  for (i = 0; i < MAX; i++){
    argv[i] = NULL;
  }

  size_t size;
  pid_t pid;

  while(1){
     bool inFlag = false;
     bool outFlag = false;
     int count = 0;
     int count2 = 0;
     redir_out = false;
     redir_in = false;
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

   // Ignore stale args
   argv[count] = NULL;
   inFlag = findRedirect(argv[0], fIn, "<");
   outFlag = findRedirect(argv[count - 1], fOut, ">");

//   for(int k = 0; k < MAX; k++){
   //   printf("argv[%d]: %s\n", k, argv[k]);
  //    printf("fOut[%d]: %c\n", k, fOut[k]);
  //    printf("fIn[%d]: %c\n", k, fIn[k]);
//   }
   for(int i = 0; i<count; i++){
   //setting up pipes
      if(inFlag || outFlag || count > 0){
         pipe(fd);
         pid = fork();
      
         if(pid > 0){
            if(count > 1){
               close(fd[0]);
               close(fd[1]);
            }
            wait(&status);
         }
         else if(pid == 0){
            if(inFlag && !outFlag && i == 0){
               printf("running inflag\n:");
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

      for(int k = 0; k < MAX; k++){
        printf("argv[%d]: %s\n", k, argv[k]);
  //    printf("fOut[%d]: %c\n", k, fOut[k]);
  //    printf("fIn[%d]: %c\n", k, fIn[k]);
      }
         int argvLength = strlen(argv[i]);
         char *argCopy = (char *)malloc(argvLength + 1 * sizeof(char));
         strncpy(argCopy, argv[i], argvLength);

         int i = 0;
         char *argP[15] = {};
         char *arg = strtok(argCopy, " ");
         do{
            int subArgLen = strlen(arg);
            argP[i] = (char *)malloc((subArgLen + 1) * sizeof(char));
            strncpy(argv[i++], arg, subArgLen);
         }
         while((arg = strtok(NULL, " ")) && i < 15);
         argP[i] = NULL;
         free(argCopy);
    for(int k = 0; k < MAX; k++){
   //     printf("argP[%d]: %s\n", k, argP[k]);
  //    printf("fOut[%d]: %c\n", k, fOut[k]);
  //    printf("fIn[%d]: %c\n", k, fIn[k]);
    }
         execvp(argv[0], (char *const *)argv);
      }
      }
    }
  }
}


bool findRedirect(char *arg, char *reFile, char *delim){
  bool flag = false;
  char *match = strtok(arg, delim);
  if (match != NULL){
    trim(match);
    strcpy(arg, match);
  }
  else
    return flag;

  match = strtok(NULL, " ");
  if (match != NULL){
    trim(match);
    strcpy(reFile, match);
    flag = true;
  }
  return flag;
}

void trim(char *str)
{
  if (!str)
    return;

  char *ptr = str;
  int len = strlen(ptr);

  while (len - 1 > 0 && isspace(ptr[len - 1]))
    ptr[--len] = 0;

  while (*ptr && isspace(*ptr))
    ++ptr, --len;

  memmove(str, ptr, len + 1);
}
