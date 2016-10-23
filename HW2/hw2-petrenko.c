#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int cs531_system(char *s); //Run command line s
void sig_handler(int signo); //Handle signals

pid_t child, wpid;


int main(int argc, char *argv[])
{
	
	//printf("length of argv %lu and the string is \n", strlen(argv[1]));
		
	int status;

	if(argc!=2)
	{
		printf("The Command Line Argument is invalid.\n");
		printf("Please enter a cmd argument using the following syntax\n");
		printf("./program ""command (such as ping)"" \n");
		printf("Program is exiting\n");
		return 0;
	}
	else
	{
	
	status = cs531_system(argv[1]);  // Processes the argv[1] command
	return status;
	}
}

int cs531_system(char *s)
{
	int cstatus;
	signal(SIGINT,sig_handler);
	signal(SIGQUIT,sig_handler);
	signal(SIGTSTP,sig_handler);


	child = fork(); // Create child process
	
	if (child==0) // Check if child process
	{
		// Execute user input command s

		execlp("sh","sh","-c",s,(char *) NULL); // Comment this to test against the systems function

		//system(s); //uncomment this to test against the systems function

		// If child process gets this far, execlp failed

		printf("\nChild process failed to execute input command %s\n",s);

		exit(EXIT_FAILURE);
	}
	else // Parent process
	{
		if (child==(pid_t)(-1)) // Check if fork() failed
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		

		//Wait for child to execute the input command


		wpid=waitpid(child,&cstatus,WUNTRACED|WCONTINUED);

		// if(WIFSIGNALED(cstatus)){printf("\n Child %d Exited with status %d\n",child, WTERMSIG(cstatus));} //Degug this to understand the status on the EXIT
	}

	return 0;
}


void sig_handler(int signo)
{

	int ccstatus;

	if (signo==SIGINT)

		printf("\nChild received SIGQUIT, Quitting Child %d and execlp %d\n",child,child+1);
		
	if (signo==SIGQUIT)
	{	
		kill(child,SIGINT); 	//Terminates the Child proccess
		kill(child+1,SIGINT);	//Terminates the execlp in the child process
		printf("\nChild received SIGQUIT, Quitting Child %d and execlp %d\n",child,child+1);
	}		

	if (signo==SIGTSTP)
	{	
		kill(child,SIGINT); 	//Terminates the Child proccess
		kill(child+1,SIGINT);	//Terminates the execlp in the child process
		printf("\nChild received SIGSTOP, Quitting Child %d and execlp %d\n",child,child+1);
	}		



}
