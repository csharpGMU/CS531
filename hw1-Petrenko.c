#include <stdio.h>  
#include <string.h>
#include <stdlib.h>


void    bubble_sort(char**,int);
int	err_chk(char**,char*,int);
void	clean(char*);    
void	print(char**);

#define NUMSTRINGS 10
#define MAXSTR 25
#define MINSTR 1


int main()    
{    
	int  t,c,n, err,len;
	long d,swap;
	char *array[100];
	char m[MAXSTR+2];   
 	
	n=NUMSTRINGS;


	/*Getting the string here */
	for(c=0;c<n;c++) 
	{
		err=0;
		printf("Enter %d string out of %d elements ",c+1,n);
		fgets(m,MAXSTR+2,stdin);

		len=strlen(m);

		clean(m); /* Clean the string from Enter strokes */
		
		err = err_chk(array,m,c); /*Error checking function */
		
		/*If error exists then this loop will keep asking for new inputs until errors are cleared out */
		while(err==1)
		{
			fgets(m,100,stdin);

			clean(m); /* Clean the string from Enter strokes */
			
			err = err_chk(array,m,c); /* The error check the new string */
		}

		array[c]=(char *) malloc((strlen(m)+1)*sizeof(char));
		strcpy(array[c],m);

	}    

	/*This is going to sort the array in ascending order*/

	bubble_sort(array, n);

	/* This is going to print the array */
    
	print(array);

	printf("String with lower ascii value: %s\n", array[0]);
	printf("String with highest ascii value: %s\n", array[NUMSTRINGS-1]);

return 0;    
}    


void print(char *list[])
{
	
	char order='\0';
	int c=0,complete=1;
	
	printf("Would you like to pring int (A)scending order of (D)escending order? \n");


	while(complete==1)
	{
		scanf("%s",&order);
		if(order=='A')
		{
			for(c=0;c<NUMSTRINGS;c++)
				{
					printf("%s\n", list[c]);
				}
			complete=0;	
		}    
	
		else if(order=='D')
		{
			for(c=(NUMSTRINGS-1);c>=0;c--)
				{
					printf("%s\n", list[c]);
				}
			complete=0;	
		}
		else {printf("Input should be A or D. Please try again");}

	}
}



/* This function will clean a fgets() input from trailing linebreaks */

void clean(char m[])
{

	int str_len,n=0;

	str_len=strlen(m);
	
	while(m[n] != '\0')
	{

		if (m[n]=='\n')
		{
			
			m[n]='\0';
			
		}	
	n++;
	}

	

}

/* THIS FUNCTION WILL TEST FOR DUPLICATES */

int err_chk(char *list[], char entry[], int c)
{

	int n,d,wp,comp_val;
	n=0; d=0; comp_val=0;




	/* if string is longer than 25 characters */
	if( strlen(entry)>MAXSTR)
	{
		printf("ERROR: The string %s is longer than 25 chars, plz re-enter\n", entry);
		
		while((getchar())!='\n'){}	
		
		d=1;	
	}
	/* if string is NULL */
	else if(entry==NULL)
	{
		printf("ERROR: The string %s is NULL , plz re-enter\n", entry);
		d=1;	
	}
	/* if string has a length less than 10 chars*/
	else if(strlen(entry)<MINSTR)
	{
		printf("ERROR: The string length %s less than 1 char , plz re-enter\n", entry);
		d=1;	
	}
	/* if string is a duplicate*/
	else
	{


		while(n < c)
		{

			comp_val=strcmp(entry,list[n]);

			if(comp_val==0)
			{
				printf("ERROR: %s is Duplicate. Please re-enter string \n", entry);			
				d=1;				
			}
			n=n+1;	
		}
	}



return d;
}


void  bubble_sort(char *list[], int n)    
{

	int c,d,comp=0;
	char *t;

	for(c=0;c<(n-1);c++)
	{
		for(d=0;d<(n-c-1);d++)
		{
			comp=strcmp(list[d],list[d+1]);

			if(comp > 0)
			{
			t=list[d];
			list[d]=list[d+1];
			list[d+1]=t;
				
			}
		
		}		
	}
}

