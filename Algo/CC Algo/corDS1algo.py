# Test du 20 septembre 2018

'''
Exercice 1 : jour de la semaine
'''
def jour(jj, mm, aa)
# application directe des formules de l'énoncé
  if mm < 3:
    z = aa-1
  else:
     z = aa
  D = 23*mm//9 + jj + 4 + aa + z//4 - z//100 + z//400
  if mm < 3:
    D = D%7
  else:
    D = (D-2)%7
  print(D)
  # ou :
  #print(['dimanche','lundi','mardi','mercredi','jeudi','vendredi','samedi'][D])
  
'''
Exercice 2 : on teste si une liste est triée
'''
def estTrie(liste):
# on vérifie si l'élément courant est bien inférieur ou égal à l'élément suivant
# des indices 0 à n-2 (iclus)
  for i in range(len(liste)-1):
    if liste[i] > liste[i+1]: # inversion : échec
      return False

  # on a tout vérifié : c'est trié
  return True

'''
Exercice 3 : inversion d'une liste
'''
def inverser(liste):
# inversion de la liste avec mofification de la liste initiale
  i = 0
  k = len(liste)-1
  # on permute les éléments d'indices i et k tant que les indices
  # ne se sont pas croisés
  while i<k :
    liste[i], liste[k] = liste[k], liste[i]
    i += 1
    k -= 1
  return liste

'''
Exercice 4 : intersection de deux listes triées
'''
def inter(liste1, liste2):
# on applique le même principe que pour l'algorithme d'interclassement
# étudié en cours
  n1 = len(liste1)
  n2 = len(liste2)
  res = []
  i1 = 0
  i2 = 0
  while (i1 < n1) and (i2 < n2) :
    if liste1[i1] < liste2[i2] : # on progresse dans la première liste
      i1 += 1
    elif liste1[i1] > liste2[i2] : # on progresse dans la deuxième liste
      i2 +=1
    else : # égalité
      # on ajoute l'élément et on progressevdans les deux listes
      res.append(liste1[i1])
      i1 += 1
      i2 += 2
  # fin de la boucle
  return res

'''
Exercice 5 : inégalité triangulaire
'''
def ineg(mat):
# on vérifie l'inégalité pour tout couple i, j avec i <= j
# car la matrice est symétrique, on vérifie la diagonale dans
# la mesure où il n'est pas précisé qu'elle est nulle
# (on pourrait aussi considérer l'autre 1/2 matrice
  n = len(mat)
  for i in range(n):
    for j in range(i+1, n): # vérification pour mat[i][j]
       mij = mat[i][j]
       for k in range(n):
         if mat[i][k] + mat[k][j] < mat[i][j]: # inégalité non vérifiée
           return False
  # fin de la boucle principale, on a tout vérifié
  return True



  
