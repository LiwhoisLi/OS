#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

int count,i=0;
void print(int n)
{
	printf("Count is %d,my pid is %d\n",count,getpid());
	i=1;		//Using a flag rather than directly setting count to 0
	return;
}

int main(void)
{
	static struct sigaction act;
	act.sa_handler = &print;
	sigfillset(&(act.sa_mask));
	sigaction(SIGALRM,&act,NULL);
	pid_t pid,pid1;
	pid = fork();
	if(pid)
	{
		pid1 = pid;
		pid = fork();
		if(pid)
		{
			for ( count=0; count<5; count++)
			{
				sleep(1);
				kill(pid, SIGALRM);
				kill(pid1,SIGALRM);
			}
			sleep(1);			//Dealing with the problem in Minix that signal cannot be handled instantly
			kill(pid, SIGSTOP);
			kill(pid1,SIGSTOP);
		}
	}
	if(!pid)	
		for( count=0; 1; count++)
			if(i)
			{
				count = 0;
				i = 0;
			}

	return 1;
}
