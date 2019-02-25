import random

#exo1
def fact(n):
    if n == 0 or n == 1:
        return 1
    
    return n*fact(n-1)

#exo2
def PGCD(a,b):
    if b == 0:
        return a
    
    return PGCD(b, a % b)

##print(PGCD(35,7))

#exo3

listeDicho = []
for i in range(100):
    listeDicho.append(random.randint(0,100))
listeDicho.sort()

def dichotomie(listeDicho, nbRecherche, inf, sup):
    i = (sup+inf)//2
##    print("i", i)
##    print("sup", sup)
##    print("inf", inf)
    if len(listeDicho[inf:sup]) == 1:
        if listeDicho[i] == nbRecherche:
            return("le nombre recherché est à l'indice {} de la iste {}".format(i, listeDicho))
        else:
            return("votre nombre n'est pas dans la liste {}".format(listeDicho))
    else:
        if nbRecherche > listeDicho[i]:
            inf = i+1

        elif nbRecherche < listeDicho[i]:
            sup = i-1
            
        else:
            return("le nombre recherché est à l'indice {} de la iste {}".format(i, listeDicho))
            
        return dichotomie(listeDicho, nbRecherche, inf, sup)

##print(dichotomie(listeDicho, int(input("Veuillez entrer le nombre recherché : ")), 0, 99))

#exo4
def NbChiffres(n, base, i=1):
        
    if n/base <= 1:
        return i
    else:
        return NbChiffres(n/base, base, i+1)

##print(NbChiffres(17,16))

#Q3
def Convert(chiffre, base):
    quot = chiffre//base
    if quot == 0:
        return str(chiffre%base)
    else:
        return(Convert(quot, base) + str(chiffre%base))

##print(Convert(64,16))

#ex5

def trirapide(L):
    """trirapide(L): tri rapide (quicksort) de la liste L"""
    def trirap(L, g, d):
        pivot = L[(g+d)//2]
        i = g
        j = d
        while True:
            while L[i]<pivot:
                i+=1
            while L[j]>pivot:
                j-=1
            if i>j:
                break
            if i<j:
                L[i], L[j] = L[j], L[i]
            i+=1
            j-=1
        #les if sont de l'opti
        #ne trie pas non plus les tabs de 3 elmts deja tries
        if g<j: #ne le fait pas si le tableau n'a qu'un element, si pas de if, max recursion error
            #cette condition permet aussi de ne pas trier a gauche les tab de 4 elmts dont les 2 1ers sont deja tries
            trirap(L,g,j)
        if i<d: #ne trie pas non plus les tableaux de deux chiffres triés
            trirap(L,i,d)
 
    g=0
    d=len(L)-1
    trirap(L,g,d)


l = []
for i in range(500000):
    l.append(random.randint(0,500000))
    
trirapide(l)
#print(l)


"""def quicksort(liste):
    print("longueur ", len(liste))
    print(liste[-1])
    if len(liste) <= 1:
        return
    sup = len(liste)
    pivot = liste[-1]
    indInf = 0
    indSup = len(liste)-2
    for i in range(len(liste)):
        print("i", i)
        print("indInf", indInf)
        print("indSup", indSup)
        
        if liste[i] <= pivot:
            indInf += 1
        else:
            liste[i], liste[indSup] = liste[indSup], liste[i]
            i -= 1
    #liste[-1], liste[indInf] = liste[indInf], liste[-1]
    return(quicksort(liste[:indInf])+quicksort(liste[indInf:]))"""

    
            
    
                
            
            
    

