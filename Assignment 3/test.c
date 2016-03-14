#include<minix/type.h>
#include<unistd.h>
#include<stdio.h>

void main()
{
  int i;
  for(i=0;i<0;i++){
    sleep(15);
    fork();
    printf("new process is forked\n");
  }
  pause();
}
