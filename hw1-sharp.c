#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMSTRINGS 10
#define TRUE 1

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
  int order, i;

  //Assign null pointers to array to avoid spurious pointer
  for(i = 0; i<NUMSTRINGS;i++)
    theStrings[i] = NULL;

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
    int c;

    printf("Enter string %d: ",i+1);

    /*28 Characters read in accounted by:
          25 - Permissable user input length
           1 - Newline character from fgets
           1 - Null terminator
           1 - Over-length detection*/
    result = fgets(inputStr,28,stdin);

    //printf("length: %d",strlen(inputStr));

    //Set newline to Null
    for(c = 0;c < 27 && inputStr[c];c++)
      if(inputStr[c]=='\n')
        inputStr[c]='\0';

    //printf(" newlength: %d\n",strlen(inputStr));

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

    //Check if we duplicate any strings
    for(c=0; c < i; c++)
    {
      if(strcmp(inputStr,stringArray[c])==0)
      {
        printf("Error: String duplicates one already entered; please choose another string\n");
        i--;
        continue;
      }
    }

    //Store our inputted strings
    str = malloc(25*(sizeof(char))); //TODO: Add catch for failed malloc
    strcpy(str,inputStr);
    stringArray[i] = str;
    }
    return;
}

int getOrder()
{
  char input;

  while(TRUE)
  {
    printf("\nPrint character strings in (A)scending or (D)escending order: ");

    input = getchar();

    if(input == 'A' || input == 'a')
      return 1;
    if(input == 'D' || input == 'd')
      return -1;

    printf("\nInvalid input - Please enter the letter 'A' or the letter 'D'");
  }
}

void freeStrings(char *stringArray[],int count)
{
  int i;
  for(i = 0; i<count;i++)
    if(stringArray[i]!=NULL)
      free(stringArray[i]);
  return;
}

void sortStrings(char *stringArray[], int size, int order)
{
  while(TRUE)
  {
    int flag = 0;
    int i;

    for(i=0; i < size-1; i++)
    {
      if(strcmp(stringArray[i],stringArray[i+1]) * order > 0)
      {
        char *temp;
        temp = stringArray[i];
        stringArray[i] = stringArray[i+1];
        stringArray[i+1] = temp;
        flag = 1;
      }
    }
    if(flag!=0)
      continue;
    else
      return;
  }
}

void printStrings(char *stringArray[], int size)
{
  int i;
  for(i=0;i<size;i++)
    printf("%s\n",stringArray[i]);

  int high, low;

  if(strcmp(stringArray[0],stringArray[size-1])>0)
  {
    high = size -1;
    low = 0;
  }
  else
  {
    high = 0;
    low = size -1;
  }


  printf("String with lowest ascii value: %s\n",stringArray[low]);
  printf("String with highest ascii value: %s\n",stringArray[high]);

  return;
}
