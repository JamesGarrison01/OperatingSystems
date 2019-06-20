#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int ENTRIES = 20;


int main(int argc, char *argv[]){

char **usCity = (char **)malloc(ENTRIES * sizeof(char *));
int cityPop[20];
int cityCount = 0;
char *line;
size_t size;

for(int i = 0; i < ENTRIES; i++){
   usCity[i] = NULL;
}

while(1){

   if(getline(&line, &size, stdin) == EOF){
      break;
   }
   else{
      usCity[cityCount] = (char *)malloc(sizeof(char) * (size + 10));
      strncpy(usCity[cityCount], line, size);

      if(getline(&line, &size, stdin) == EOF){
         break;
      }
      else if(atoi(line) > 15){
         cityPop[cityCount++] = atoi(line);
      }
      else{
         free(usCity[cityCount]);
      }
   }
}
//for(int i = 0; i < cityCount; i++){
int i = 0;
while(usCity[i] != NULL){
   if(cityPop[i] > 15)
      printf("%s", usCity[i++]);
}
return(0);
}
