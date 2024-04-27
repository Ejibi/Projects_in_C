#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * current = WHITE;

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
}

void answer_checker(char *targetted,char *target,char *given){
  int length = strlen(target);
  for(int i=0;i < length; ++i){
    if (target[i] == given[i]){
      setColour(GREEN);
            printf("%c", given[i]);
    }
    else{
      int k=0;
      for(int f = 0;f<length; ++f){
          if(targetted[f] == given[i] && target[f] != given[f])
          { setColour(YELLOW);
           printf("%c", given[i]); 
           targetted[f]='\0';
            ++k;
            break;
            }
            }
      if (k == 0){
        setColour(WHITE); printf("%c", given[i]);}
        }
      }
      printf("\n");
        }
        
int main(int argc, char **argv){
  if (argc != 2 ){
    printf("No word given");
    return 1;
  }
  char *arr = argv[1];
  char *new_arr = strdup(argv[1]);
  int k = 0;
  char words[14];
  while(k < 7){
    setColour(WHITE);
    printf("Enter guess: ");
    scanf("%s", words);
    if (strlen(words)==strlen(arr)){
      answer_checker(new_arr,arr,words);
      strcpy(new_arr, arr);
      if (strcmp(words,arr) == 0){
        setColour(WHITE);
        printf("Finished in %d guesses\n", k+1);
        break;
      }
      if (strcmp(words,arr) != 0){
        k=k+1;
      }
      if (k == 6){
        setColour(WHITE);
        printf("Failed to guess the word: %s\n", arr);
        break;
        }
    }
    else{
      printf("Invalid guess, guess length must match word length\n");
      break;
    }
    }
  free(new_arr);
  }
  
  
