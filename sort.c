#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


static int ENTRIES = 20;

void swap(char **a, char **b);

int main(int argc, char *argv[]){

char **usCity = (char **)malloc(ENTRIES * sizeof(char *));
int cmpVal;
char cityPop[20];
int cityCount = 0;
char *line;
size_t size;

for(int i = 0; i <= ENTRIES; i++){
   usCity[i] = NULL;
}

printf("\nHit ctrl D to Quit\n");

while(1){

   printf("\nEnter a city name\n");
   if(getline(&line, &size, stdin) == EOF){
      break;
   }
   else{
      usCity[cityCount] = (char *)malloc(sizeof(char) * (size + 10));
      strncpy(usCity[cityCount], line, size);
      printf("\nEnter population (2digits)\n");
      if(getline(&line, &size, stdin) == EOF){
        break;
      }
      else if(atoi(line) > 15){
        cityPop[cityCount] = atoi(line);
        cityCount = cityCount + 1;
      }
      else{
         free(usCity[cityCount]);
      }
   }
}

printf("\n\nSuccessfully Exited. Results:\n");
for (int i = 0; i < cityCount; i++){
    for (int j = i + 1; j < cityCount; j++)    {
      cmpVal = strcasecmp(usCity[i], usCity[j]);
      if (cmpVal > 0)
        swap(&usCity[i], &usCity[j]);
      else if (cmpVal == 0)
        if (isupper(usCity[i][0]))
          swap(&usCity[i], &usCity[j]);
    }
}

for(int c = 0; c < cityCount; c++){
   printf("%s", usCity[c]);
   free(usCity[c]);
}
exit(0);
}

void swap(char **a, char **b)
{
  char *temp = *a;
  *a = *b;
  *b = temp;
}
