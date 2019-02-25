import random
import time

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
        if g<j:
            trirap(L,g,j)
        if i<d:
            trirap(L,i,d)
 
    g=0
    d=len(L)-1
    trirap(L,g,d)
    return L


def tri_selection(tableau):
    nb = len(tableau)
    for en_cours in range(0,nb):    
        plus_petit = en_cours
        for j in range(en_cours+1,nb) :
            if tableau[j] < tableau[plus_petit] :
                plus_petit = j
        if min is not en_cours :
            temp = tableau[en_cours]
            tableau[en_cours] = tableau[plus_petit]
            tableau[plus_petit] = temp



def tri_insertion(tableau):
    for i in range(1,len(tableau)):
        en_cours = tableau[i]
        j = i
        #décalage des éléments du tableau }
        while j>0 and tableau[j-1]>en_cours:
            tableau[j]=tableau[j-1]
            j = j-1
        #on insère l'élément à sa place
        tableau[j]=en_cours
    return tableau



def tri_bulle(tableau):
    permutation = True
    passage = 0
    while permutation == True:
        permutation = False
        passage = passage + 1
        for en_cours in range(0, len(tableau) - passage):
            if tableau[en_cours] > tableau[en_cours + 1]:
                permutation = True
                # On echange les deux elements
                tableau[en_cours], tableau[en_cours + 1] = \
                tableau[en_cours + 1],tableau[en_cours]
    return tableau  



def generationTab(taille):
    tab = []
    for i in range(taille):
        tab.append(random.randint(0,taille))
    return tab

tab100 = generationTab(100)
tab100bis = tab100[:]
tab100ter = tab100[:]
tab100qua = tab100[:]
tab1000 = generationTab(1000)
tab1000bis = tab1000[:]
tab1000ter = tab1000[:]
tab1000qua = tab1000[:]
tab10000 = generationTab(10000)
tab10000bis = tab10000[:]
tab10000ter = tab10000[:]
tab10000qua = tab10000[:]
tabSort10000 = tab10000[:]

timeStartQuicksort100 = time.time()
trirapide(tab100)
timeEndQuicksort100 = time.time()
timeQuicksort100 = timeEndQuicksort100-timeStartQuicksort100

timeStartQuicksort1000 = time.time()
trirapide(tab1000)
timeEndQuicksort1000 = time.time()
timeQuicksort1000 = timeEndQuicksort1000-timeStartQuicksort1000

timeStartQuicksort10000 = time.time()
trirapide(tab10000)
timeEndQuicksort10000 = time.time()
timeQuicksort10000 = timeEndQuicksort10000-timeStartQuicksort10000


timeStartSelect100 = time.time()
tri_selection(tab100bis)
timeEndSelect100 = time.time()
timeSelect100 = timeEndSelect100-timeStartSelect100

timeStartSelect1000 = time.time()
tri_selection(tab1000bis)
timeEndSelect1000 = time.time()
timeSelect1000 = timeEndSelect1000-timeStartSelect1000

timeStartSelect10000 = time.time()
tri_selection(tab10000bis)
timeEndSelect10000 = time.time()
timeSelect10000 = timeEndSelect10000-timeStartSelect10000


timeStartInsert100 = time.time()
tri_insertion(tab100ter)
timeEndInsert100 = time.time()
timeInsert100 = timeEndInsert100-timeStartInsert100

timeStartInsert1000 = time.time()
tri_insertion(tab1000ter)
timeEndInsert1000 = time.time()
timeInsert1000 = timeEndInsert1000-timeStartInsert1000

timeStartInsert10000 = time.time()
tri_insertion(tab10000ter)
timeEndInsert10000 = time.time()
timeInsert10000 = timeEndInsert10000-timeStartInsert10000


timeStartBulle100 = time.time()
tri_bulle(tab100qua)
timeEndBulle100 = time.time()
timeBulle100 = timeEndBulle100-timeStartBulle100

timeStartBulle1000 = time.time()
tri_bulle(tab1000qua)
timeEndBulle1000 = time.time()
timeBulle1000 = timeEndBulle1000-timeStartBulle1000

timeStartBulle10000 = time.time()
tri_bulle(tab10000qua)
timeEndBulle10000 = time.time()
timeBulle10000 = timeEndBulle10000-timeStartBulle10000


timeStartSort = time.time()
tabSort10000.sort()
timeSort = time.time()-timeStartSort



print("tps trirap - 100 : {}, 1000 : {}, 10000 : {}".format(timeQuicksort100,timeQuicksort1000,timeQuicksort10000))
print("tps triselect - 100 : {}, 1000 : {}, 10000 : {}".format(timeSelect100,timeSelect1000,timeSelect10000))
print("tps triinsert - 100 : {}, 1000 : {}, 10000 : {}".format(timeInsert100,timeInsert1000,timeInsert10000))
print("tps tribulle - 100 : {}, 1000 : {}, 10000 : {}".format(timeBulle100,timeBulle1000,timeBulle10000))
print("tps sort - 10000 : {}".format(timeSort))
