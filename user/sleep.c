//#include <unistd.h>
//#include <stdlib.h>
//#include <stdio.h>
#include "user/user.h"
int main(int argc, char *argv[]){
  if(argc < 2) {
    int a = write(2,"Error\n",7);
    if(a){}
    exit(1);
  }
  int n;

  n = 0;
  while('0' <= *argv[1] && *argv[1] <= '9')
    n = n*10 + *argv[1]++ - '0';
  
  sleep(n); 
  exit(0);
  return 0;
}
