import math
import random

#exo1
#la fonction racine retourne un tableau contenant les racines
def racines(a,b,c):
    tabRacines = []
    delta = b**2 - 4 * a * c
    if delta > 0:
        tabRacines.append((-b - math.sqrt(delta))/2*a)
        tabRacines.append((-b + math.sqrt(delta))/2*a)
    elif delta == 0:
        tabRacines.append((-b)/2*a)
    else:
        tabRacines.append(complex(-b/2*a, -math.sqrt(abs(delta))/2*a))
        tabRacines.append(complex(-b/2*a, +math.sqrt(abs(delta))/2*a))
    return tabRacines


#exo2
def perim(rayon):
    return 2*math.pi*rayon

def surf(rayon):
    return math.pi*rayon**2
    
def perimEtSurf(rayon):
    return {'perimetre' : perim(rayon), 'surface' : surf(rayon)}

def surfEtVol(rayon, hauteur):
    return {'surface' : surf(rayon)*2 + perim(rayon)*hauteur, 'volume' : surf(rayon)*hauteur}


#exo3
def trouveTonNombre(nombre):
    nb = int(input('ton nombre : '))
    while nb != nombre:
        if nb > nombre:
            print("C'est moins")
        else:
            print("C'est plus")
        nb = int(input('ton nombre : '))
    print("Bravo, tu as trouve le nombre mystère : " + str(nombre))

##trouveTonNombre(random.randint(0,100))


#exo4
def trouveMonNombre(nombre):
    inf = 0
    sup = 100
    guess = random.randint(inf, sup)
    while guess != nombre:

        plusOuMoins = input('ce nombre est-il plus ou moins grand (+/-) : ' + str(guess) + ' ? ')
        
        if plusOuMoins == '+':
            sup = guess
            
        elif plusOuMoins == '-':
            inf = guess

        guess = random.randint(inf, sup)

    print("c'est gagné; le nombre était : " + str(nombre))

##trouveMonNombre(45)
    
#exo5
def rencontre(N, J, M, N1):

    if M == 1:
        if N%2 == 0:
            aDom = N1
        else:
            return(None, None)
    elif M > 1:
        aDom = ((J+M-2)%(N1-1))+1

    aLext = ((J-M+N1-1)%(N1-1))+1

    return(aDom, aLext)

def championnat(N):
    
    if N%2 != 0:
        N1 = N+1
    else:
        N1 = N
        
    nbJ = N1-1
    nbM = int(N1/2)

    for J in range(1, nbJ+1):
        for M in range(1, nbM+1):
            match = rencontre(N, J, M, N1)
            print("Le match " + str(M) + " de la journée " + str(J) + " oppose l'équipe " \
                  + str(match[0]) + " à domicile à l'équipe " + str(match[1]) + " à l'extérieur.") 
    
##print(championnat(5))


#exo6

#technique "algo" : while avec des indices ou avec le code ascii
def verifNombre(N):

    for i in range(len(N)):
        if not('0' <= N[i] <= '9'):
            return False

    return True

##print(verifNombre(input("entrez un nombre : ")))
            
    

#exo7

def chrToInteger(chaine):
    result = 0
    k=0
    for i in range(len(chaine)-1, -1, -1):
        result += (ord(chaine[i]) - ord('0'))*10**k
        k += 1
    return result
    

def calc(ope):
    operateur = ['+', '-', '*', '/', '%', '//']
    i=0
    for caract in ope:

        if verifNombre(caract):
            i = i+1
        else:
            if caract in operateur:
                premierNb = chrToInteger(ope[:i])
                break
            else:
                print("Ce que vous avez entré n'est pas une opération sur des nombres")
                return
            
    for caract2 in ope[i+1:-1]:
        if not(verifNombre(caract2)):
            print("Ce que vous avez entré n'est pas une opération sur des nombres")
            return

    deuxiemeNb = chrToInteger(ope[i+1:-1])

    if ope[-1] == '=':
        
        if ope[i] == operateur[0]:
            print(premierNb + deuxiemeNb)
        elif ope[i] == operateur[1]:
            print(premierNb - deuxiemeNb)
        elif ope[i] == operateur[2]:
            print(premierNb * deuxiemeNb)
        elif ope[i] == operateur[3]:
            print(premierNb / deuxiemeNb)
        elif ope[i] == operateur[4]:
            print(premierNb % deuxiemeNb)
        elif ope[i] == operateur[5]:
            print(premierNb // deuxiemeNb)
        else:
            print("Votre opérateur n'est pas accepté")
            
    else:
        print("Vous n'avez pas mis de =")

    return

##calc(input("Entrez votre opération (opérateurs acceptés ['+', '-', '*', '/', '%', '//']) : "))


#exo8
def saisieListe():
    liste = []
    x=input("Entrez un nouvel élément : ")
    while x != "":
        liste.append(x)
        x=input("Entrez un nouvel élément : ")
    return liste

##print(saisieListe())


#exo9
def mini(l):
    minL = l[0]
    for i in range(len(l)):
        if l[i] < minL:
            minL = l[i]
    return minL

def maxi(l):
    maxL = l[0]
    for i in range(len(l)):
        if l[i] > maxL:
            maxL = l[i]
    return maxL

def moyenne(l):
    moy = 0
    for i in range(len(l)):
        moy += l[i]

    return moy/len(l)
    
def minMaxEtMoyenne():
    liste = []
    x=int(input("Entrez un nouvel élément : "))
    while x != "":
        liste.append(x)
        print("Le min : " + str(mini(liste)) + ", le max : " + str(maxi(liste)) + ", la moyenne " + str(moyenne(liste)))
        x=int(input("Entrez un nouvel élément : "))


#exo10
def inversion(liste):
    if type(liste) == str:
        liste = list(liste)
    for i in range(len(liste)//2):
        liste[i], liste[len(liste)-i-1] = liste[len(liste)-i-1], liste[i]
    return liste

##print(inversion(saisieListe()))

#exo11
def pairsImpairs():
    liste = []
    newListe = []
    for i in range(10):
        liste.append(random.randint(0, 100))
    print(liste)
    
    for j in range(len(liste)):
        if liste[j] % 2 == 0:
            newListe.insert(0, liste[j])
        else:
            newListe.append(liste[j])
    return newListe

##print(pairsImpairs())

#exo12
def palindrome():
    liste = saisieListe()
    for i in range(len(liste)):
        if list(liste[i]) == inversion(liste[i]):
            print(liste[i])

##palindrome()

#exo13
def triABulles():
    liste = []
    for i in range(10):
        liste.append(random.randint(0, 100))

    print(liste)
    
    for j in range(len(liste)-1):
        for k in range(len(liste)-1):
            if liste[k]>liste[k+1]:
                liste[k], liste[k+1] = liste[k+1], liste[k]

    print(liste)

triABulles()


