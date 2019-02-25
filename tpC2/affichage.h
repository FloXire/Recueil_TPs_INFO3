#ifndef H_AFFICHAGE // si H_AFFICHAGE n'a pas encore été définit
#define H_AFFICHAGE // on le definit

void printTab(int *tab, int tailleTab);
int verifTabTrie(int *tab, int tailleTab, int (*fctComp)(int, int));
void printTrie(int *tab, int tailleTab, int (*fctComp)(int, int));
int (*menu(void))(int, int);

#endif /* guard */
