#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  //printf("%s\n", argv[1]);
  DIR *dirp;
  struct dirent *dptr;
  if((dirp = opendir("."))==NULL) { //opendir renvoie l'adresse du directory
    printf("error\n");
    return(-1);
  }

  while ((dptr=readdir(dirp))) {
    printf("%s\n", dptr->d_name);
  }
  closedir(dirp);

  return 0;
}
