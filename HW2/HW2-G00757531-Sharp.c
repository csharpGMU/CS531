/*
	Homework #2 - CS 531-002

	Team members:
		Joseph Carter - G00867175
		Stanislav Petrenko - G00383728
		Christopher Sharp - G00757531
*/

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PATH_TO_SHELL "/bin/sh"

void sig_handler(int signo);
int cs531_system(char *s);


int main(int argc, char *argv[])
{
	char command[256];

	if(argc>1) //Execute the argument
	{
		cs531_system(argv[1]);
	}
	else //Enter interactive command mode
	{
		//Continuously execute this loop until explicitly exited
		while(1==1)
		{
			//Interactively get new command
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

int cs531_system(char *s)
{
	pid_t child, wpid;
	int cstatus;

	//Register signal handlers for process prior to fork()
	signal(SIGINT,sig_handler);
	signal(SIGTERM,sig_handler);
	signal(SIGTSTP,sig_handler);
	signal(SIGQUIT,sig_handler);

	child = fork(); // Create child process

	if (child==0) // Check if child process
	{
		// Execute user input command s
		execlp(PATH_TO_SHELL,PATH_TO_SHELL,"-c",s,(char *) NULL);

		// If child process gets this far, execlp failed
		printf("Child process failed to execute input command %s",s);
		_exit(EXIT_FAILURE);
	}
	else // Parent process
	{
		if (child==(pid_t)(-1)) // Check if fork() failed
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}

		//Wait for child to execute the input command
		wpid = waitpid(child,&cstatus,0);

		//Deregister signal handlers
		signal(SIGINT, SIG_DFL);
		signal(SIGTERM,SIG_DFL);
		signal(SIGTSTP,SIG_DFL);
		signal(SIGQUIT,SIG_DFL);
	}

	return 0;
}

void sig_handler(int signo)
{
	if (signo==SIGINT)
		printf("\n\nChild received SIGINT\n");
	else if (signo==SIGTERM)
		printf("\n\nChild received SIGTERM\n");
	else if (signo==SIGTSTP)
		printf("\n\nChild received SIGSTP\n");
	else if (signo==SIGQUIT)
		printf("\n\nChild received SIGQUIT\n");
}
