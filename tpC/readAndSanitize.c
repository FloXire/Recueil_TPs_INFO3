#include <stdio.h>
#include <string.h>

int main() {

  char isInt = 0;

  while (!isInt) {

    char c[255];
    fgets(c, 255, stdin);

    isInt = 1;

    for(int i = 0; i<(strlen(c)-1); i++) {
      if (!(c[i] >= '0' && c[i] <= '9')) {
        isInt = 0;
      }
    }

    if (isInt) {
      printf("Voici votre nombre : %s\n", c);
    }
    else {
      printf("Erreur, rentre un nombre fdp !\n");
    }

  }

}
