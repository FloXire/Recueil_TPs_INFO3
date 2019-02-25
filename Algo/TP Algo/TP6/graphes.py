def isOrientedMat(mat):
    nbLetC = len(mat)
    for i in range(nbLetC):
        for j in range(i):
            if mat[i][j] != mat[j][i]:
                return True

    return False

def isOrientedList(dico):
    for item in dico.items():
        for voisin in item[1]:
            if not(item[0] in dico[voisin]):
                return True

    return False

def dicoToMat(dico):
    nbSommets = len(dico.keys())
    mat = []
    for i in range(nbSommets):
        mat.append([0]*nbSommets)
    
    for item in dico.items():
        for voisin in item[1]:
            mat[int(item[0])][int(voisin)] = 1

    return mat

def matToDico(mat):
    dico = {}
    n = len(mat)
    for i in range(n):
        listeI = []
        for j in range(n):
            if int(mat[i][j]) == 1:
                listeI.append(j)
        dico[i] = listeI

    return dico

def ajoutOrientation(dicoInit):
    dico = {}
    dico["oriente"] = isOrientedList(dicoInit)
    dico["listes"] = dicoInit
    return dico    

def numeroteArcs(dico):
    listeArcs = []
    i = 0
    if dico["oriente"]:
        # on n'a pas de couples identiques
        for key in dico["listes"].keys():
            for val in dico["listes"][key]:
                listeArcs.append((i, (key, val)))
                i += 1
            
    else:
        for key in dico["listes"].keys():
            for val in dico["listes"][key]:
                djaPrez = False
                for j in range(len(listeArcs)):
                    if listeArcs[i][1] == (key, val):
                        djaPrez = True
                        break
                if not(djaPrez):
                    listeArcs.append((i, (val, key)))
                    i += 1

    dico["listeArcs"] = listeArcs
    
    return dico

def nbArcs(dico):
    return len(dico["listeArcs"])

def dicoToMatInc(dico):
    print(dico)
    nbCol = nbArcs(dico) # nb arcs
    nbLigne = len(dico["listes"].keys()) # nb sommets
    mat = []
    for i in range(nbLigne):
        mat.append([0]*nbCol)
        
    if dico["oriente"]:
        for j in range(nbCol):
            mat[dico["listeArcs"][j][1][0]][j] = -1
            mat[dico["listeArcs"][j][1][1]][j] = 1
        
    else:
        for j in range(nbCol):
            mat[dico["listeArcs"][j][1][0]][j] += 1
            mat[dico["listeArcs"][j][1][1]][j] += 1

    return mat

dicAdj = {0 : [1], 1 : [2], 2 : [0]}

matriceAdj = [
    [1,1,1,0,1],
    [1,0,0,0,0],
    [1,0,0,0,0],
    [1,0,0,0,0],
    [1,0,0,0,0]]

#print(dicoToMatInc(numeroteArcs(ajoutOrientation(dicAdj))))

# structure de données permettant de stocker les listes d’adjacence d’un graphe
# {valeurSommet : [valeurVoisin1, valeurVoisin2, ...], ...}

# structure de données permettant de stocker les listes d’adjacence d’un graphe et le caractère orienté ou non
# {"oriente" : True/False, "listes" : {valeurSommet: [valeurVoisin1, valeurVoisin2, ...], ...}}


class Graphe:
    def __init__(self, sommets = [], arcs = [], oriente = None):
        self.sommets = sommets
        self.arcs = arcs
        self.oriente = oriente

    def ajouterArete(self, arc):
        self.arcs.append(arc)

    def indiceArc(self, numeroArc):
        for i in range(len(self.arcs)):
            if self.arcs[i].numeroArc == numeroArc:
                return i
        return None

    def supprimerArete(self, numeroArc):
        indice = self.indiceArc(numeroArc)
        if indice:
            del self.arcs[indice]

    def listeAdjacence(self, valeurSommet):
        listeAdj = []
        if self.oriente:
            for arc in self.arcs:
                if arc.sommet1.valeurSommet == valeurSommet:
                    listeAdj.append(arc.sommet2.valeurSommet)
        else:
            for arc in self.arcs:
                if arc.sommet1.valeurSommet == valeurSommet:
                    listeAdj.append(arc.sommet2.valeurSommet)
                if arc.sommet2.valeurSommet == valeurSommet:
                    listeAdj.append(arc.sommet1.valeurSommet)
                    
        return listeAdj

    def nombreSommets(self):
        return len(self.sommets)

    def nombreAretes(self):
        return len(self.arcs)

    def transfo(self):
        if self.oriente == True:
            self.oriente = False
        elif self.oriente == False:
            self.oriente == True    
    
    
class Sommet:
    def __init__(self, valeur = None):
        self.valeur = valeur

class Arc:
    def __init__(self, sommet1 = None, sommet2 = None, numeroArc = None):
        self.sommet1 = sommet1
        self.sommet2 = sommet2
        self.numeroArc = numeroArc

listeSommets = []
for i in range(10):
    listeSommets.append(Sommet(i))

listeArcs = []
for i in range(len(listeSommets)-1):
    listeArcs.append(Arc(listeSommets[i], listeSommets[i+1], i))

listeArcs.append(Arc(listeSommets[-1], listeSommets[0], listeArcs[-1].numeroArc+1))
    
G = Graphe(listeSommets, listeArcs)
G.transfo()
#print(G.oriente)

"""
for sommet in G.sommets:
    print(sommet.valeur)

for arc in G.arcs:
    print(arc.sommet1.valeur, arc.sommet2.valeur, arc.numeroArc)
"""

# exo 2
import random

graphe = [
    [1,0,1,1,1],
    [0,0,1,0,0],
    [1,1,0,0,0],
    [1,0,0,0,0],
    [1,0,0,0,0]]

def nonOrienteToRandomOriente(graphe):
    cote = len(graphe)
    for i in range(cote):
        for j in range(i+1,cote):
            if graphe[i][j] == 1:
                if random.random() < 0.5:
                    graphe[i][j] = 0
                else:
                    graphe[j][i] = 0
    return graphe

#print(nonOrienteToRandomOriente(graphe))

def creationRandomGraphe(n, p):
    graphe = []
    for i in range(n):
        graphe.append([0]*n)

    for i in range(n):
        for j in range(n):
            if random.random() <= p:
                graphe[i][j] = 1

    return graphe

grapheExo3 = creationRandomGraphe(10,0.90)

# exo 3

# qu 1

def parcoursLargeur(graphe):
    # idée : tester pour chaque sommet le parcours en largeur, jusqu'à retrouver tous les sommets
    parcours = []
    djaParcouru = []
    distsommet = [0]*len(graphe)
    
    while len(parcours) != len(graphe):
        if len(djaParcouru) == 0:
            for cpt, elmt in enumerate(graphe[0]):
                if elmt == 1:
                    parcours.append(cpt)
            djaParcouru.append(0)
            
        else:
            aParcourir = set(parcours) - set(djaParcouru)

            for sommet in aParcourir:
                for cpt, elmt in enumerate(graphe[sommet]):
                    if elmt == 1 and cpt not in parcours:
                        parcours.append(cpt)
                djaParcouru.append(sommet)

    return parcours

##print(parcoursLargeur(graphe))

grapheProf = [
    [1,1,1,0,0],
    [1,1,0,1,1],
    [1,0,1,0,0],
    [0,1,0,1,0],
    [0,1,0,0,1]]

def parcoursProfondeurRecursif(graphe, sommet = 0, listeParcours = []):

    listeParcours.append(sommet)
    
    for sommet, elmt in enumerate(graphe[sommet]):
        if elmt == 1 and sommet not in listeParcours:
            parcoursProfondeurRecursif(graphe, sommet, listeParcours)

    return listeParcours

#print(parcoursProfondeurRecursif(grapheProf))

def listeCompConnexes(graphe):

    tab =  [i for i in range(len(graphe))]

    for i in range(len(graphe)):
        for j in range(i+1, len(graphe)):
            if graphe[i][j] == 1:
                tab[j] = tab[i]

    return tab

graphe = [
    [0,5,8,0,0],
    [5,0,2,1,0],
    [8,2,0,0,6],
    [0,1,0,0,0],
    [0,0,6,0,0]]

#print(listeCompConnexes(graphe))

#exo 4

import copy

def kruskal(graphe, sommetInit):
    arbreMin = copy.deepcopy(graphe)
    arbreResult = [[0 for i in range(len(graphe))] for j in range(len(graphe))]
    arbreMin[sommetInit] = [0 for i in range(len(graphe))]
    sommetAdd = [sommetInit]
    while len(sommetAdd) != len(graphe):        
        mini = (54545454544,-1,-1)
        for sommet in sommetAdd:
            for i in range(len(graphe)):
                if arbreMin[i][sommet] !=0 and arbreMin[i][sommet] < mini[0]:
                    mini = (arbreMin[i][sommet], i, sommet)
        arbreMin[mini[1]] = [0]*len(graphe)
        sommetAdd.append(mini[1])
        arbreResult[mini[1]][mini[2]] = 1
        arbreResult[mini[2]][mini[1]] = 1
    return arbreResult

for i in range(len(graphe)):
    print(kruskal(graphe,1)[i])
            

#exo5

'''
En théorie des graphes, l'algorithme de Dijkstra (prononcé [dɛɪkstra]) sert à résoudre le problème du plus court chemin.
Il permet, par exemple, de déterminer un plus court chemin pour se rendre d'une ville à une autre connaissant le réseau routier d'une région.
Plus précisément, il calcule des plus courts chemins à partir d'une source dans un graphe orienté pondéré par des réels positifs.
On peut aussi l'utiliser pour calculer un plus court chemin entre un sommet de départ et un sommet d'arrivée.
https://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra
'''









                
        

