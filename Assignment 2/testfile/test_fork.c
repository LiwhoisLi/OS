#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdio.h>

int main(int argc, char **argv)
{
  pid_t pid;
  int fd,i;
  pid = fork();
  if(pid){
    wait(NULL);
  }
  else
  {
    if((fd=creat("a",O_WRONLY))==-1)
      exit(1);
    close(fd);
    unlink("a");
    pause();
  }
  return 0;
}
