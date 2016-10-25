#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define PATH_TO_SHELL "/bin/sh"

int cs531_system(const char *comm);
void cs531_system_SIGINT_handler(int sig);

int main(int argc, char *argv[])
{
	char command[256];

	if(argc>1) //Execute the argument
	{
		cs531_system(argv[1]);
	}
	else //Enter interactive command mode
	{
		while(1==1)
		{
			printf("\nPlease enter system command (QUIT to exit): ");
			fgets(command,255,stdin);

			//Test for quit
			if(strcmp(command,"QUIT\n")==0)
			{
				printf("\nGoodbye.\n");
				exit(EXIT_SUCCESS);
			}

			//Execute the command
			cs531_system(command);
		}
	}

}

int cs531_system(const char *comm)
{
	pid_t pid;
	int status;

	//Register sigint handler
	signal(SIGINT,cs531_system_SIGINT_handler);

	//Fork
	pid = fork();

	if(pid==0)
	{	//Executed if CHILD
		printf("Child process %s\n",comm);
		execl(PATH_TO_SHELL,PATH_TO_SHELL,"-c",comm,(char *)0);
		printf("Child failed\n");
		_exit(127); //Only executed on failure
	}
	else
	{ //Executed if PARENT
		printf("Parent process\n");
		waitpid(pid,&status,0);
		printf("Child died\n");
	}

	//Deregister sigint handler
	signal(SIGINT, SIG_DFL);
}

void cs531_system_SIGINT_handler(int sig)
{
	printf("CTRL-C pressed\n");
}
