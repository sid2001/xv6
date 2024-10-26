#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char*
getfilename(char* p) {
  char* ptr;
  for(ptr = p + strlen(p); ptr >= p && *ptr != '/'; ptr--)
    ;
  ptr++;
  return ptr;
}

void
find(char* dir, char* file){
  int fd;
  char buf[512], *ptr;
  struct dirent de;
  struct stat st;
  if((fd = open(dir,O_RDONLY)) < 0) {
    fprintf(2, "find: No such dir.\n");
    return;
  }
  
  if(fstat(fd, &st) < 0) {
    fprintf(2, "find: Error");
    close(fd);
    return;
  }

  switch(st.type) {
    char *p;
    case T_DEVICE:
    case T_FILE:
      p = getfilename(dir);
      if(!strcmp(p,file)) {
        printf("%s\n",dir);
      }
      close(fd);
      return;
    case T_DIR:
      if(strlen(dir) + 1 + DIRSIZ + 1 > sizeof buf) {
        printf("find: path too long\n");
        break;
      } 
      strcpy(buf,dir);
      ptr = buf + strlen(buf);
      *ptr++ = '/';
      while(read(fd,&de, sizeof(de)) == sizeof(de)) {
        if(de.inum == 0)
          continue;
        if(!strcmp(".",de.name)||!strcmp("..",de.name)){
          continue;}
        memmove(ptr, de.name, DIRSIZ);
        find(buf, file); 
      }
      break;
    default:
      fprintf(2,"Invalid type\n");
      close(fd);
      exit(1);
  }
  close(fd);
}

int main(int argc, char* argv[]) {

  if(argc<2) {
    printf("Invalid command usage\n");
    exit(1);
  }
  if(argc<3) {
    printf("Invalid options\n");
    exit(1);
  } 
  find(argv[1],argv[2]);
  
  exit(0);
}
