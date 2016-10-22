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

int main(int argc, char *argv[])
{
	//Call cs531_system() to do all processing
	int status;
	status = cs531_system(argv[1]);
	return status;
}

int cs531_system(char *s)
{
	pid_t child, wpid;
	int cstatus;

	signal(SIGINT,sig_handler);

	child = fork(); // Create child process
	
	if (child==0) // Check if child process
	{
		// Execute user input command s
		execlp("sh","sh","-c",s,(char *) NULL);
		
		// If child process gets this far, execlp failed
		printf("Child process failed to execute input command %s",s);
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
		wpid = wait(&cstatus);
	}

	return 0;
}

void sig_handler(int signo)
{
	if (signo==SIGINT)
		printf("\n\nChild received SIGTERM\n");

}


