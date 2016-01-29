#define BUFSIZE 128
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void)
{

	pid_t p1,p2;
	int pipedes[3][2];   //Each row of this array represents a pipe
	char sen[BUFSIZE], rcv[BUFSIZE];
	int i,j;
	for (i=0;i<3;i++)
	{
		if (pipe(pipedes[i])==-1)
		{
			perror("pipe call");
			exit(1);
		}
	}


	p1 = fork();
	
	if (p1)	//Parent process serves as P3
	{
		close(pipedes[0][0]);
		close(pipedes[0][1]);
		close(pipedes[1][1]);
		close(pipedes[2][0]);
		if ((read(pipedes[1][0], rcv, BUFSIZE))==-1)
		{
			perror("read call");
			exit(3);
		}
		i = 0;
		while(rcv[i++]);
	
		for(j=0;j<i;j++)	
		{
			if ( rcv[j]>='a'&&rcv[j]<='z')
				sen[j] = rcv[j]-32;
			else
				sen[j] = rcv[j];
		}
		printf("I am process P3\nMy pid is %d\nI just received the string %s\nI am sending %s to P1\n", getpid(), rcv, sen);
		if ((write(pipedes[2][1], sen, BUFSIZE))==-1)
		{
			perror("write call");
			exit(2);
		}
		wait(NULL);	
		printf("I am process P3\nMy pid is %d\nI'm about to die\n", getpid());
		exit(0);
	}
	else	
	{
		p2 = fork();
		if (p2)		//The child process serves as P2
		{
			close(pipedes[0][1]);
			close(pipedes[1][0]);
			close(pipedes[2][0]);
			close(pipedes[2][1]);
			if ((read(pipedes[0][0], rcv, BUFSIZE))==-1)
			{
				perror("read call");
				exit(3);
			}
			i = 0;
			while(rcv[i++]);
			i--;
			sen[i]=rcv[i];
			for(j=0;j<i;j++)
				sen[j] = rcv[i-1-j];
			printf("I am process P2\nMy pid is %d\nI just received the string %s\nI am sending %s to P3\n", getpid(), rcv, sen);
			if ((write(pipedes[1][1], sen, BUFSIZE))==-1)
			{
				perror("write call");
				exit(2);
			}
			wait(NULL);
			printf("I am process P2\nMy pid is %d\nI'm about to die\n", getpid());
			exit(0);
		}
		else	//Grandchild process serves as P1, because it should be firstly terminated 
		{
			close(pipedes[0][0]);
			close(pipedes[1][0]);
			close(pipedes[1][1]);
			close(pipedes[2][1]);
			printf("I am process P1\nMy pid is %d\nPlease enter a string: ", getpid());
			scanf("%s", sen);
			if ((write(pipedes[0][1], sen, BUFSIZE))==-1)
			{
				perror("write call");
				exit(2);
			}
			if ((read(pipedes[2][0], rcv, BUFSIZE))==-1)
			{
				perror("read call");
				exit(3);
			}
			
			printf("I am process P1\nMy pid is %d\nI just received the string %s\n", getpid(), rcv);

			printf("I am process P1\nMy pid is %d\nI'm about to die\n", getpid());
			exit(0);
		}
	}
	return 1;
}
