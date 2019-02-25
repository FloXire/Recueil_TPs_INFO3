#include <stdio.h>


struct match {
  int aDom, aLext;
};

struct match rencontre(int N, int N1, int J, int numMatch) {
  struct match m;

  if (numMatch == 1) {
    if (N%2 == 0) {
      m.aDom = N1;
    }
    else {
      m.aDom = 0;
    }
  }
  else if (numMatch > 1) {
    m.aDom = ((J+numMatch-2)%(N1-1))+1;
  }

  m.aLext = ((J-numMatch+N1-1)%(N1-1))+1;

  return m;
}

void championnat(int N) {

  int N1;

  if (N%2 == 0) {
    N1 = N;
  }
  else {
    N1 = N+1;
  }

  int J = N1-1;
  int nbMatchs = N1/2;

  for (int i=1; i<=J; i++) {
    for (int j=1; j<=nbMatchs; j++) {
      struct match m = rencontre(N, N1, i, j);
      printf("Le match %d de la journée %d oppose l'équipe %d à domicile à l'équipe %d à l'extérieur\n", j, i, m.aDom, m.aLext);
    }
  }
}


int main () {
  int N = 12;
  championnat(N);
  return 0;
}
