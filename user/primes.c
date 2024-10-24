#include "user/user.h"

int main(int argc, char* argv[]){
  // if(argc < 2){
  //   write(2, "Error\n",10);
  //   exit(1);
  // }
  
  int n = 0;
  while('0' <= *argv[1] && *argv[1] <= '9'){
    n = n*10 + *argv[1] - '0';
    argv[1]++;
  }

    int p[2];
    pipe(p);
    int d = 2;
    printf("prime %d\n",d);
    int pid = fork();
    int i;
    if(pid > 0){
        for(i = 2; i <= 35; i++) {
            if(i%d!=0){
                write(p[1],(void *)&i,sizeof(int));
            }
        }
        close(p[0]);
        close(p[1]);
        wait(0);
    }else if(pid == 0){
        close(p[1]);
        close(0);
        dup(p[0]);
        close(p[0]);
        int flag = 1;
        int first = 1;
        int n;
        int p2[2];
        while(1) {
            if(read(0,(void *)&n,sizeof(int))<1){
                //cout<<"finished for "<<d<<"\n";
                close(p2[1]);
                close(0);
                wait(0);
                exit(0);
            }
            if(first){
                first = 0;
                d = n;
                printf("prime %d\n",d);
            }
            if(n%d!=0&&flag) {
                flag = 0;
                pipe(p2);
                if(fork()==0){
                    close(p2[1]);
                    flag = 1;
                    first = 1;
                    close(0);
                    dup(p2[0]);
                    close(p2[0]);
                }else{
                    close(p2[0]);
                    write(p2[1],(void *)&n,sizeof(int));
                }
            }else if(n%d!=0){
                write(p2[1],(void *)&n,sizeof(int));
            }
        }
    }
    return 0;
}
