#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMSTR 10
#define MINSTRSIZE 1
#define MAXSTRSIZE 25

void get_user_str(int, char**);
int check_for_duplicates(int, char*, char**);
void sort_string_array(int, char**) ;
void print_string_array(char**);

int main() 
{
	int i;
	char* str_ptr[NUMSTR];

	// Get user input
	for (i=0; i<NUMSTR; i++)
	{	
		get_user_str(i,str_ptr);
	}


	// Sort user input strings
	sort_string_array(NUMSTR,str_ptr);

	// Print strings
	print_string_array(str_ptr);

	return 0;

}

void get_user_str(int i, char* str_ptr[])
{
	int not_assigned=1,  dup_flag, c;
	int str_length;
	char temp_str[MAXSTRSIZE+2];

	while (not_assigned) // Loop until user inputs a valid string
	{ 

		// Get string from user
		printf("Enter String %d: ",i+1);
		fgets(temp_str,MAXSTRSIZE+2,stdin);
		str_length = strlen(temp_str);

		// Remove trailing '\n' if it exists
		if ( temp_str[str_length-1] == '\n' )
		{
			temp_str[str_length-1] = '\0';
			str_length--; // Decrement count because '\n' removed
		}

		// Check length for errors and ask again (loop) if not a valid input
		if (str_length>MAXSTRSIZE) 
		{
			printf("\nError: The entered text too long. Please try again.\n");
			// Since fgets only read in part of the entered text, clear the rest
			while ( (c=getchar()) != '\n') {} // Read input until newline found
			continue; // Go back to beginning of while-loop to ask again
		}
		else if (str_length<MINSTRSIZE) 
		{
			printf("\nError: The entered text is too short. Please try again\n");
			continue; // Go back to beginning of while-loop to ask again
		}
		else 
		{
			if (i==0) // First input string
			{
				str_ptr[i] = (char *) malloc((str_length+1)*sizeof(char)); // Allocate
				strcpy(str_ptr[i],temp_str); // Copy input to string array
				not_assigned=0; // Exit loop
			}
			else // Not first input string
			{
				dup_flag = check_for_duplicates(i,temp_str, str_ptr);

				if (dup_flag)
					printf("\nError: This text was already entered. Try again:\n");
				else 
				{
					str_ptr[i] = (char *) malloc((str_length+1)*sizeof(char)); 	
					strcpy(str_ptr[i],temp_str); // Copy input to string array
					not_assigned = 0; // Exit loop
				}					
			}
		}
	}
}

int check_for_duplicates(int n_str, char temp_str[], char *str_ptr[])
{
	int j,compare_val,dup_flag=0; // 0=no duplicates found

	for (j = 0; j<n_str; j++) // Loop through strings already entered (n_str)
	{
		compare_val = strcmp(temp_str,str_ptr[j]);
		if (compare_val==0)
		{
			dup_flag = 1; // Indicate duplicate found
			break; // Exit loop to return dup_flag
		}
	}

	return dup_flag;
}

void sort_string_array(int n, char *str_ptr[]) 
{
	/* This function sorts an array of strings in ascending order.
	Input n is number of strings and str_ptr is arrary of strings */

	int c,d, compare_val;
	char *swap; // To temporarily save address of a string for swapping

	for (c=0; c<n-1; c++) // Loop through partial list n-1 times, list getting smaller each time
	{
		for (d=0; d<n-c-1; d++) // Loop through list, "pushing" larger values down the list
		{
			compare_val = strcmp(str_ptr[d],str_ptr[d+1]);
			
			if (compare_val>0) // First one larger, "push" it down the list
			{
				swap = str_ptr[d];
				str_ptr[d] = str_ptr[d+1];
				str_ptr[d+1] = swap;
			}
			else if (compare_val==0)
				printf("Error: Program did not detect duplicate!\n");
			//else if (compare_val<0) // Second one larger, do nothing
		}
	}
}

void print_string_array(char *str_ptr[])
{
	int i;
	char order='\0', try_again=1;

	while (try_again)
	{
		printf("\nPrint strings in Ascending or Descending order:");
		scanf("%c",&order);

		if (order=='A')
		{
			printf("Ascending order:\n\n");
			for (i = 0; i < NUMSTR; i++)
			{
				printf("%s \n",str_ptr[i]);
			}
			try_again = 0; // User gave valid input
		}
		else if (order=='D')
		{
			printf("\n\n Descending order:\n\n");
			for ( i = (NUMSTR-1); i >= 0; i--)
			{
				printf("%s \n",str_ptr[i]);
			}
			try_again = 0; // User gave valid input
		}
		else
			printf("Error: Please enter 'A' or 'D'");
	}

	// Print lowest and highest ASCII value strings
	printf("\nString with lowest ascii value: %s",str_ptr[0]);
	printf("\nString with highest ascii value: %s\n",str_ptr[NUMSTR-1]);
}




