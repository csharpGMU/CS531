#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMSTRINGS 10

void getStrings(char *stringArray[],int count);
int getOrder();
void freeStrings(char *stringArray[],int count);
void stringOrder();
void sortStrings(char *stringArray[], int size, int order);
void printStrings(char *stringArray[], int size);

//TODO: Needs lots of comments

int main()
{
  char *theStrings[NUMSTRINGS];
  int order;

  printf("\nEnter %d character strings:\n\n",NUMSTRINGS);

  getStrings(theStrings,NUMSTRINGS);

  order = getOrder();

  sortStrings(theStrings,NUMSTRINGS,order);

  printStrings(theStrings,NUMSTRINGS);

  //Free the malloc'd memory containing the strings
  freeStrings(theStrings,NUMSTRINGS);

  return 0;
}

void getStrings(char *stringArray[],int count)
{
  int i;
  for(i = 0;i<count;i++)
  {
    char *str;
    char inputStr[28];
    char *result;

    printf("Enter string %d: ",i+1);

    /*28 Characters read in accounted by:
          25 - Permissable user input length
           1 - Newline character from fgets
           1 - Null terminator
           1 - Over-length detection*/
    result = fgets(inputStr,28,stdin);

    printf("length: %d",strlen(inputStr));

    //Set newline to Null
    int c;
    for(c = 0;c < 27 && inputStr[c];c++)
      if(inputStr[c]=='\n')
        inputStr[c]='\0';

    printf(" newlength: %d\n",strlen(inputStr));

    //Check if we are Over-length
    if(strlen(inputStr)>25)
    {
      printf("Error: String length is too long - please re-enter\n");
      char c;
      if(strlen(inputStr)>26)
        while(c = getchar() != '\n' && c != -1)
          {/*Do nothing; consume stdin buffer*/}
      i--;
      continue;
    }

    //TODO:Check if we depulicate any strings

    //Store our inputted strings
    str = malloc(25*(sizeof(char))); //TODO: Add catch for failed malloc
    strcpy(str,inputStr);
    stringArray[i] = str;
    }
    return;
}

int getOrder()
{

  return 0;
}

void freeStrings(char *stringArray[],int count)
{

  return;
}

void stringOrder()
{

  return;
}

void sortStrings(char *stringArray[], int size, int order)
{

  return;
}

void printStrings(char *stringArray[], int size)
{
  int i;
  for(i=0;i<size;i++)
    printf("%s\n",stringArray[i]);

    //TODO: Add the part about lowest/highest

  return;
}
