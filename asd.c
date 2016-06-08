#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<wait.h>

int main()
{
	pid_t pid; 
	pid = fork();
	if(pid == 0)
{
	printf("\nPID=%d\n, PPID=%d\n", getpid(), getppid());

}
	else
{

	printf("PID=%d zav \n");

}
}
