import random
import time

labyrinthe=[[1,1,1,1,1,1,1,1,1,1], \
            [1,3,1,0,0,0,0,0,0,1], \
            [1,0,1,1,1,1,0,1,0,1], \
            [1,0,0,0,1,1,0,1,0,1], \
            [1,0,1,1,1,1,0,1,0,1], \
            [1,0,1,0,1,1,0,1,0,2], \
            [1,0,1,0,0,0,0,1,1,1], \
            [1,0,1,0,1,1,0,0,0,1], \
            [1,0,0,0,1,1,0,1,0,1], \
            [1,1,1,1,1,1,1,1,1,1]]

def trajet(labyrinthe):

    placePerso = (1,1)
    trajet = []
    global victoire
    victoire = False
    
    def sortie(labyrinthe, placePerso, trajet):
        print(placePerso)
        global victoire
        if placePerso in trajet:
            return
        if labyrinthe[placePerso[0]][placePerso[1]] == 2:
            print("c'est gagné")
            victoire = True
            return

        trajet.append(placePerso)
        
        listeNextMovePossib = [] #liste de coord des mouvements possibles au prochain coup
        if labyrinthe[placePerso[0]-1][placePerso[1]] in (0,2): #en haut
            listeNextMovePossib.append((placePerso[0]-1, placePerso[1]))
        if labyrinthe[placePerso[0]+1][placePerso[1]] in (0,2): #en bas
            listeNextMovePossib.append((placePerso[0]+1, placePerso[1]))
        if labyrinthe[placePerso[0]][placePerso[1]-1] in (0,2): #a gauche
            listeNextMovePossib.append((placePerso[0], placePerso[1]-1))
        if labyrinthe[placePerso[0]][placePerso[1]+1] in (0,2): #a droite
            listeNextMovePossib.append((placePerso[0], placePerso[1]+1))

        for i in range(len(listeNextMovePossib)):
            if victoire:
                return
            sortie(labyrinthe, listeNextMovePossib[i], trajet)
            

    sortie(labyrinthe, placePerso, trajet)

start = time.time()
trajet(labyrinthe)
print(str(time.time()-start))

"""a = {1:2}
a[2]=3
print(a)

def inDico(dico, cle, placeAPrendre):
    if placeAPrendre == -1:
        if cle in dico:
            return True
    if (cle in dico) and (placeAPrendre in dico[cle]):
        return True
    else:
        return False

def trajetIter(labyrinthe):

    placePerso = (1,1)
    dicoComportement = {(1,1):[]}
    print(dicoComportement)
    
    while labyrinthe[placePerso[0]][placePerso[1]] != 2:
        print(placePerso)
        #peut etre faire avec une liste de croisements et de trajet, revenir au dernier croisement
        #quand on est revenu sur nos pas
        if labyrinthe[placePerso[0]-1][placePerso[1]] in (0,2) and \
           not(inDico(dicoComportement, placePerso, (placePerso[0]-1,placePerso[1]))): #en haut
            if not(inDico(dicoComportement, placePerso, -1)):
                dicoComportement[placePerso] = []
            dicoComportement[placePerso].append((placePerso[0]-1,placePerso[1]))
            placePerso = (placePerso[0]-1,placePerso[1])
        elif labyrinthe[placePerso[0]+1][placePerso[1]] in (0,2) and \
           not(inDico(dicoComportement, placePerso, (placePerso[0]+1,placePerso[1]))): #en bas
            if not(inDico(dicoComportement, placePerso, -1)):
                dicoComportement[placePerso] = []
            dicoComportement[placePerso].append((placePerso[0]+1, placePerso[1]))
            placePerso = (placePerso[0]+1,placePerso[1])
        elif labyrinthe[placePerso[0]][placePerso[1]-1] in (0,2) and \
           not(inDico(dicoComportement, placePerso, (placePerso[0],placePerso[1]-1))): #a gauche
            if not(inDico(dicoComportement, placePerso, -1)):
                dicoComportement[placePerso] = []
            dicoComportement[placePerso].append((placePerso[0], placePerso[1]-1))
            placePerso = (placePerso[0],placePerso[1]-1)
        elif labyrinthe[placePerso[0]][placePerso[1]+1] in (0,2) and \
           not(inDico(dicoComportement, placePerso, (placePerso[0],placePerso[1]+1))): #a droite
            if not(inDico(dicoComportement, placePerso, -1)):
                dicoComportement[placePerso] = []
            dicoComportement[placePerso].append((placePerso[0], placePerso[1]+1))
            placePerso = (placePerso[0],placePerso[1]+1)
        
trajetIter(labyrinthe)"""
