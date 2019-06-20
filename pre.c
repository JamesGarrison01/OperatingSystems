#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

char usCity[20][30] = { "" };
int cityPop[20];
int cityCount = 0;
char *line;
size_t size;

printf("\nHit ctrl D to Quit\n");

while(1){

   printf("\nEnter a city name\n");
   if(getline(&line, &size, stdin) == EOF){
      break;
   }
   else{
         strcpy(usCity[cityCount], line);
      printf("\nEnter population (2digits)\n");
      if(getline(&line, &size, stdin) == EOF){
         break;
      }
      else{
         cityPop[cityCount] = atoi(line);
      }
      cityCount = cityCount + 1;
   }
}
printf("\n\nSuccessfully Exited. Results:\n");
for(int i = 0; i <= cityCount; i++){
   if(cityPop[i] > 10)   
      printf("%s", usCity[i]);
      //puts(usCity[i]);
}
exit(0);
}
