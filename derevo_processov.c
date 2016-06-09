#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

	int main()
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		execl("/home/2016/shurin/File_Manager/Fail_Manager", "Fail_Manager", (char*)0);
		_exit(0);
	}
	else
		wait(0);
}
