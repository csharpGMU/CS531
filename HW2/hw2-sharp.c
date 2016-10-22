#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int cs531_system(const char *comm);

int main(int argc, char *argv[])
{
	if(argc>1)
		cs531_system(argv[1]);
	else
		cs531_system("aaa");

	return 0;

}

int cs531_system(const char *comm)
{
	int pid;

	//Register sigint handler
	signal(SIGINT,cs531_system_SIGINT_handler(&pid));	

	//Fork
	pid = fork();

	if(pid==0)
	{	//Executed if CHILD
		printf("Child process");
		execlp(comm); //Fix this
		_exit(1);
	}
	else // Executed if PARENT
	{
		printf("Parent process");
		wait();
		printf("Child died");
	}
	
	//Deregister sigint handler
	signal(SIGINT, SIG_DFL);
}

int cs531_system_SIGINT_handler(int *pid)
{
	printf("CTRL-C pressed; PID: %d\n",*pid);
}
