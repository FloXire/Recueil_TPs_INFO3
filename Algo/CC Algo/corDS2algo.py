# Exercie 1 : arbres binaires de recherche : voir poly


# Exercice 2.1 : décomposition en carrés, version irérative
def decomp(n):
  res = []
  # boucle principale : soustraction du plus grand carré
  while n > 0:
    rac = n**0.5 # racine carré
    carre = int(rac)**2
    # carre = (rac//1)**2 version sans utiliser int
    res.append(carre) # ajout à la liste
    n = n-carre
  #n end while
  return res

# Exercice 2.2 : version récursive
def decompRec(n):
  if n== 0:
    return []
  else:
    # recherche et soustraction du grand grand carré
    rac = n**0.5 # racine carrée
    carre = int(rac)**2
    n = n-carre
    # appel et récursif et retour du résultat
    return [carre]+decompRec(n)
# exemple d'appel principal : liste = decompRec(10)


# Exercice 3 : suite de Syracuse (jusqu'à 1), version récursive
def syracuse(u):
  if u == 1:
    return [1] # arrêt de la récursivité
  # terme suivant
  elif u%2 == 0: # si pair
    u1 = u//2
  else : # si impair
    u1 = 3*u+1
  # appel récursif et retour du résultat
  return [u]+syracuse(u1)
# exemple d'appel principal : liste = syracuse(10)


# Exercice 4 : nombres premiers avec le crible d'Eratosthene
# version itérative ou récursive
def eratosthene(n):
  # tableau de booléens de 0 à n initialisé à True
  # perte de 2 cases pour 0 et 1, optimisation mémoire en exercice
  premier = [True]*(n+1)
  fin = int(n**0.5)+1
  # boucle principale à partir de 2 jusqu'à sqrt(n)
  for i in range(2,fin):
    if premier[i]:  # si i est un nombre premier
      k = i*i
      while k <= n : # on barre tous les multiples de i à oartir de i**2
        premier[k] = False
        k = k+i
      # end while
  # end for
  # restitution du résultat
  res = []
  for i in range(2, n+1):
    if premier[i]:
      res.append(i)
  return res


# Exercice 5 : affichage des nombres parfaits
# version itérative ou version récursive
def parfait(n):
  for i in range(2,n+1): # 0 et 1 ne sont pas des nombres parfaits
    # calcul de la somme des diviseurs de i
    somDiv = 0
    for j in range(1,i//2+1): # on ne considère pas le nombre lui-même
      if i%j==0 : # j est un diviseur de i
        somDiv = somDiv+j
    # il n'y a plus qu'à tester
    if i == somDiv:
      print(i)
# fin de la fonction


###########################################################################
# EXEMPLE TYPE DE PROGRAMME RECURSIF FAUX pour la question 3
# c'est d'ailleurs le même problème pour la question 2.2
def syracuseFaux(u, res=[]):
  res.append(u)
  if  u==1:
    return res
  elif u%2==0:
    syracuseFaux(u//2, res)
  else:
    syracuseFaux(3*u+1, res)
# La récursivité comprend 2 phases : une phase de descente dans les
# appels récursifs et une phase de remontée.
# Après la phase de descente, la liste contient bien le résultat mais
# le return n'empèche pas la phase de remontée et à la fin la fonction
# renvoie None.
# La note mise pour ce type de fonctions est de 25% (ou moins en cas
# d'autres erreurs).



      
  

    
