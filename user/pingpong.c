//#include <unistd.h>
//#include <sys/types.h>
//#include <stdio.h>
#include "user/user.h"
#include "kernel/types.h"

int main() {
  char byte = 'a'; 
  int a;
  int p1[2], p2[2];
  if(pipe(p1)== -1 || pipe(p2) == -1) {
    a = write(2,"Error piping!\n",14);
    exit(a);
  }

  int pid = fork();

  if(pid > 0) {
    int ppid = getpid();
    close(p1[0]);
    close(p2[1]);
    if(write(p1[1],&byte,1)!=1){
      exit(1);
    }
    if(read(p2[0],&byte,1)!=1){
      exit(1);
    } else {
      fprintf(2,"%d: received pong\n",ppid);
    }
  } else {
    close(p1[1]);
    close(p2[0]);
    
    if(read(p1[0],&byte,1)!=1){
      exit(1);
    } else {
      fprintf(2,"%d: received ping\n",getpid());
    }

    if(write(p2[1],&byte,1)!=1){
      exit(1);
    }
  }
  exit(0);

}

