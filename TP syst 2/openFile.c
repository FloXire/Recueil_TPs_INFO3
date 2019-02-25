#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h> //pour le O_RDONLY
#include <string.h>

int main(int argc, char *argv[]){
  int fd;
  char *path;
  char buff[4096];
  int n;

  if (argc != 2){
  	fprintf(stderr, "syntax : %s chemin\n", argv[0]);
  	exit(1);
  }
  path = argv[1];

  system(strcat("file ", path));

  if((fd = open(path, O_RDONLY))==-1){
  	perror(path);
  	exit(1);
  }
  while ((n = read(fd, buff, 4096))>0){
  	printf("%d caracteres lus\n", n);
  	(void)write(1, &buff[0], n);
  }
  if(n==-1){
  	perror(path);
  	exit(1);
  }
  (void)close(fd);

  return 0;

}
