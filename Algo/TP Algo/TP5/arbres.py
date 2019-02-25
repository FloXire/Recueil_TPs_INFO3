import random

class Tree:
    def __init__(self, rac = None, ag = None, ad = None):
        self.racine = rac
        self.arbreG = ag
        self.arbreD = ad

    def node(self):
        return (self.racine, self.arbreG.racince, self.arbreD.racine)

    def term(self):
        pass

    def empty(self):
        return self.racine == None

    def root(self):
        return self.racine
    
    def depth(self):
        if self.arbreG == None and self.arbreD == None:
            d=0
        else:
            depthG = 0
            depthD = 0
            if self.arbreG != None:
                depthG=self.arbreG.depth()
            if self.arbreD != None:
                depthD=self.arbreD.depth()

            d= 1+max(depthG, depthD)

        return d

    def nb_node(self):
        
        nb = 0
        if self.arbreG == None and self.arbreD == None:
            nb = 0

        elif self.arbreG != None and self.arbreD != None:
            nb = 2 + self.arbreG.nb_node() + self.arbreD.nb_node()

        elif self.arbreG != None:
            nb = 1 + self.arbreG.nb_node()

        elif self.arbreD != None:
            nb = 1 + self.arbreD.nb_node()
            
        return nb

    def somme(self):
        
        if self.arbreG == None and self.arbreD == None:
            s=self.racine
            
        else:
            sg = 0
            sd = 0
            if self.arbreG != None:
                sg = self.arbreG.somme()
            if self.arbreD != None:
                sd = self.arbreD.somme()

            s = self.racine + sd + sg

        return s

        

"""g = Tree(1, Tree(0))
d = Tree(4, Tree(3, Tree(5, Tree(6))), Tree(5))
a = Tree(2, g, d)

print(a.nb_node())"""

class Node:
    def __init__(self, val = None, noeudG = None, noeudD = None):
        self.valeur = val
        self.gauche = noeudG
        self.droite = noeudD

class BinTree:
    def __init__(self, rac):
        #racine est une instance de la classe noeud
        self.racine = rac

    def infixe(self):
        if self.racine.valeur != None:
            self.racine.gauche.infixe()
            print(self.racine.valeur)
            self.racine.droite.infixe()

    def insertRec(self, val):
        if self.racine.valeur == None:
            self.racine = Node(val, BinTree(Node()), BinTree(Node()))
            
        elif val <= self.racine.valeur:
            self.racine.gauche.insertRec(val)
            
        else:
            self.racine.droite.insertRec(val)

    def insertIter(self, val):
        racineEncours = self
        while racineEncours.racine.valeur != None:
            #print(racineEncours.racine.valeur)
            if racineEncours.racine.valeur <= val:
                racineEncours = racineEncours.racine.droite
            else:
                racineEncours = racineEncours.racine.gauche

        racineEncours.racine = Node(val, BinTree(Node()), BinTree(Node()))

    def searchRec(self, val):
        retour = None
        if self.racine.valeur == val:
            retour = True
        elif self.racine.valeur == None:
            retour = False
        elif self.racine.valeur < val:
            retour = self.racine.droite.searchRec(val)
        else:
            retour = self.racine.gauche.searchRec(val)

        return retour

    def searchIter(self, val):
        racineEncours = self
        while racineEncours.racine.valeur != val and racineEncours.racine.valeur != None:
            if racineEncours.racine.valeur < val:
                racineEncours = racineEncours.racine.droite
            else:
                racineEncours = racineEncours.racine.gauche

        return racineEncours.racine.valeur == val


"""a = BinTree(Node(4, BinTree(Node()), BinTree(Node())))
b = BinTree(Node(6, BinTree(Node()), BinTree(Node())))

arbre = BinTree(Node(5, a, b))
arbre.insertRec(5)
#arbre.infixe()
arbre.insertIter(30)
#arbre.infixe()
#print(arbre.searchRec(530))
#print(arbre.searchIter(5))

liste = [random.randint(0,1000) for i in range(1000)]"""

def triBin(liste):
    arbre = BinTree(Node(liste[0], BinTree(Node()), BinTree(Node())))
    for nb in liste:
        arbre.insertRec(nb)
    arbre.infixe()

#triBin(liste)

ope = "+ - 4 2 * 3 5"

i = 0
while i < len(ope):
    if ope[i] == " ":
        i+=1
    elif '0' <= ope[i] <= "9":
        tmp = ope[i]
        i += 1
        while '0' <= ope[i] <= "9":
            tmp += ope[i]
            i += 1
        BinTree(Node(tmp, BinTree(Node()), BinTree(Node())))
    else: # if operande
        BinTree(ope[i], nbGauche, nbDroite





