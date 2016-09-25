#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMSTRINGS 10 //The number of strings we will collect from user
#define TRUE 1

void getStrings(char *stringArray[],int count);
int getOrder();
void freeStrings(char *stringArray[],int count);
void stringOrder();
void sortStrings(char *stringArray[], int size, int order);
void printStrings(char *stringArray[], int size, int order);

int main()
{
  char *theStrings[NUMSTRINGS];
  int order, i;

  //Assign null pointers to array to avoid spurious pointer
  for(i = 0; i<NUMSTRINGS;i++)
    theStrings[i] = NULL;

  printf("\nEnter %d character strings:\n\n",NUMSTRINGS);

  //Handle input of strings, check for duplicates and correct length
  getStrings(theStrings,NUMSTRINGS);

  order = getOrder();

  sortStrings(theStrings,NUMSTRINGS,order);

  //Free the malloc'd memory containing the strings
  freeStrings(theStrings,NUMSTRINGS);

  return 0;
}

//Function to handle input of strings from user; checks for over/under length
//also check for duplicates
void getStrings(char *stringArray[],int count)
{
  int i;
  for(i = 0;i<count;i++)
  {
    char *str;
    char inputStr[28];
    char *result;
    int c, dupeFlag;

    printf("Enter string %d: ",i+1);

    /*28 Characters read in accounted by:
          25 - Permissable user input length
           1 - Newline character from fgets
           1 - Null terminator
           1 - Over-length detection*/
    result = fgets(inputStr,28,stdin);

    //Set newline to Null
    for(c = 0;c < 27 && inputStr[c];c++)
      if(inputStr[c]=='\n')
        inputStr[c]='\0';

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

    //Check if we are under-length
    if(strlen(inputStr)<1)
    {
      printf("Error: String length is too short - please re-enter\n");
      i--;
      continue;
    }

    //Check if we duplicate any strings
    dupeFlag = 0;
    for(c=0; c < i; c++)
      if(strcmp(inputStr,stringArray[c])==0)
        dupeFlag=1; //Set flag indicating duplicate
    if(dupeFlag==1)
    {
        printf("Error: String duplicates one already entered; please choose another string\n");
        i--;
        continue;
    }

    //Store our inputted strings
    str = malloc(25*(sizeof(char)));
    strcpy(str,inputStr);
    stringArray[i] = str;
  }//End For-loop

  return;
}

//Asks user if order should be ascending or descending
//Returns 1 for ascending, -1 for descending
int getOrder()
{
  char input;

  //Keep looping until we get a valid input and return
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

//Free all dynamically allocated strings pointed to by stringArray
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
  //Keep looping until we have one pass of no-flips
  while(TRUE)
  {
    int flag = 0; //Flag indicates if we've flipped entries on this pass
    int i;

    //Iterate through the array of strings
    for(i=0; i < size-1; i++)
    {
      //strcmp * order; where order = {1,-1}, ascending/descending is flipped
      //based on sign of the order variable
      if(strcmp(stringArray[i],stringArray[i+1]) * order > 0)
      {
        //Given out-of-order pair of entres, swap the variables
        char *temp;
        temp = stringArray[i];
        stringArray[i] = stringArray[i+1];
        stringArray[i+1] = temp;
        flag = 1;
      }
    }
    //If the flag has changed, we need to make another pass on the array
    if(flag!=0)
      continue;
    else //If no swap has been made on a single pass, then array is in order
      return;
  }
}

//Print out strings to the user, and indicate the highest/lowest ascii valued
void printStrings(char *stringArray[], int size, int order)
{
  int i;
  for(i=0;i<size;i++)
    printf("%s\n",stringArray[i]);

  int high, low;

  //As in sortStrings(), the sign of order flips the interpretation of strcmp()
  if(strcmp(stringArray[0],stringArray[size-1])*order>0)
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
