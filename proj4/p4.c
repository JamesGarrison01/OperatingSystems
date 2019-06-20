#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 29

int REFSIZE = 0;
int FRAMESIZE = 0;
int FAULTS = 0;

int *getRef();
void printRef(int pages[]);
void runOptimal(int pages[]);
int findMin(int hits[]);
void runLRU(int pages[]);



int main(){
   int *pages;
   pages = getRef();
   printRef(pages);
   printf("\nRUNNING LRU:\n");
   runLRU(pages);
   printRef(pages);
   printf("\nRUNNING OPTIMAL:\n");
   runOptimal(pages);
   return 0;
}

int *getRef(){
   int count = 0;
   static int pages[5];
   printf("Please enter a frame size: \n");
   scanf("%d", &FRAMESIZE);
   while(1){
      printf("Please enter a reference type -1 to exit (%d):", count);
      scanf("%d", &pages[count]);
      if(pages[count] == -1 || count == MAXSIZE)
         break;
      count++;
      REFSIZE = count;
   }
   return pages;
}

void printRef(int *pages){
   printf("REF PRAGES: ");
   for(int i = 0; i < REFSIZE; i++){
      printf("%d ", pages[i]);
   }
   printf("\n");
}

void runOptimal(int *pages){
   int temp[FRAMESIZE];
   int frames[FRAMESIZE];
   int faults = 0;
   int pos, max;
   bool flag1, flag2, flag3;
   for(int i = 0; i < FRAMESIZE; i++){
      frames[i] = -1;
   }
   for(int i = 0; i < REFSIZE; i++){
      flag1 = flag2 = 0;
      for(int j = 0; j < FRAMESIZE; j++){
         if(frames[j] == pages[i]){
            flag1 = flag2 = 1;
            break;
         }
      }
   if(flag1 == 0){
      for(int j = 0; j <FRAMESIZE; j++){
         if(frames[j] == -1){
            FAULTS++;
            frames[j] = pages[i];
            flag2 = 1;
            break;
         }
      }
   }
   if(flag2 == 0){
      flag3 = 0;
      for(int j = 0; j < FRAMESIZE; j++){
         temp[j] = -1;
         for(int k = i + 1; k < REFSIZE; k++){
            if(frames[j] == pages[k]){
               temp[j] = k;
               break;
            }
         }
      }
      for(int j = 0; j < FRAMESIZE; ++j){
                if(temp[j] == -1){
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }
            
            if(flag3 ==0){
                max = temp[0];
                pos = 0;

                for(int j = 1; j < FRAMESIZE; ++j){
                    if(temp[j] > max){
                        max = temp[j];
                        pos = j;
                    }
                }
            }
            frames[pos] = pages[i];
            faults++;
        }
        printf("\n");
        for(int j = 0; j < FRAMESIZE; ++j){
            printf("%d\t", frames[j]);
        }
    }
    
    printf("\nTotal Page Faults = %d\n", faults);
}

int findMin(int hits[]){
   int min = hits[0];
   int pos = 0;
   for(int i = 0; i < FRAMESIZE; i++){
      if(hits[i] < min){
         min = hits[i];
         pos = i;
      }
   }
   return pos;
}

void runLRU(int *pages){
   int frames[FRAMESIZE];
   int hits[FRAMESIZE];
   int pos;
   int faults = 0;
   int count = 0;
  
   for(int i = 0; i < FRAMESIZE; i++){
      frames[i] = -1;
   }
   
   for(int i = 0; i < REFSIZE; i++){
      bool flag = 0;
      for(int j = 0; j < FRAMESIZE; j++){
         if(frames[j] == -1){
            frames[j] = pages[i];
            count++;
            hits[j] = count;
            flag = 1;
            break;
         }
         else if(frames[j] == pages[i]){
            count++;
            hits[j] = count;
            flag = 1;
            break;
         }
      }
      if(flag == 0){
         pos = findMin(hits);
         frames[pos] = pages[i];
         count++;
         faults++;
         hits[pos] = count;
      }
      printf("\n");
        
        for(int j = 0; j < FRAMESIZE; ++j){
            printf("%d\t", frames[j]);
        }
    }
    
    printf("\nTotal Page Faults = %d\n\n", faults);
}
