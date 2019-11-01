#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
  DIR *dirp;
  struct dirent *dptr;
  if((dirp = opendir("rep"))==NULL) { //opendir renvoie l'adresse du directory
    printf("error");
    return(-1);
  }

  while (dptr=readdir(dirp)) {
    printf("%s\n", dptr->d_name);
  }
  closedir(dirp);

  return 0;
}
