#include<minix/type.h>
#include<unistd.h>
#include<stdio.h>

void main()
{
  int i;
  for(i=0;i<2;i++){
    sleep(5);
    fork();
    printf("new process is forked\n");
  }
  printf("My pid is %d\n",getpid());
  pause();
}
